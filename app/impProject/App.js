import React from 'react';
import { StyleSheet, View, Button, Text } from 'react-native';
import BartButton from './components/BartButton';
import BartNavBar from './components/BartNavBar';
import BartSlider from './components/BartSlider';
import BartModal from './components/BartModal';


export default function App() {
  const BLICKING_ENDPOINT = "blicking";
  const FADING_ENDPOINT = "fading";

  const [response, setResponse] = React.useState(null);
  const [error, setError] = React.useState(null);
  const [sequenceName, setSequenceName] = React.useState("none");
  const [modalVisible, setModalVisible] = React.useState(false);

  const [isBlicking, setBlicking] = React.useState(false);
  const [isFading, setFading] = React.useState(false);

  const changeIntensity = (path) => (value) => {
    fetch(`http://192.168.0.179:8282/${path}?intensity=${value}`)
      .then(response => {
        response.text()
          .then(message => {
            setResponse({
              message,
              status: response.status
            })
          })
          .catch(setError)
      })
      .catch(setError)
  }

  const setState = (expectedEndpoint, actualEndpoint, requiredState, func) => {
    if (expectedEndpoint === actualEndpoint) {
      requiredState ? func(true) : func(false);
    }
  };

  const sendRequest = (endpoint,showModal) => {
    if(showModal){
      setSequenceName(endpoint);
      setModalVisible(true);
    }

    fetch(`http://192.168.0.179:8282/${endpoint}`)
      .then(response => {
        response.text()
          .then(message => {
            setResponse({
              message,
              status: response.status
            })
          })
          .then(setModalVisible(false))
          .catch(setError)
      })
      .catch(setError)
  }

  const changeState = (path, isSequence) => (isActive) => {
    const stateMessage = isActive ? "off" : "on";
    setSequenceName(path);

    setState(BLICKING_ENDPOINT, path, !isActive, setBlicking);
    setState(FADING_ENDPOINT, path, !isActive, setFading);

    if ((isSequence || isBlicking || isFading) && !isActive) {
      setModalVisible(true);
    }
    var endpoint=path+"?state="+stateMessage;

    sendRequest(endpoint);
  }

  return (
    <View style={styles.container}>
      <BartNavBar />
      <BartModal visible={modalVisible} nameOfSequence={sequenceName} onClose={() => setModalVisible(false)} />
      <View style={{ flex: 2, flexDirection: "row" }}>

        <BartButton onPress={changeState("red")} color="#FF5964" title="Red" isLight={true} sequence={isBlicking || isFading} />
        <BartButton onPress={changeState("green")} color="#6BF178" title="Green" isLight={true} sequence={isBlicking || isFading} />
        <BartButton onPress={changeState("blue")} color="#35A7FF" title="Blue" isLight={true} sequence={isBlicking || isFading} />
      </View>

      <View style={{ flex: 4, flexDirection: "row" }}>
        <BartSlider onChange={changeIntensity("red")} />
        <BartSlider onChange={changeIntensity("green")} />
        <BartSlider onChange={changeIntensity("blue")} />
      </View>
 
      <View style={{ flex: 2, flexDirection: "row" }}>
        <BartButton onPress={changeState("blicking")} color="#E2C044" title="Blicking" sequence={isFading} />
        <BartButton onPress={changeState("fading")} color="#BA5A31" title="Fading" sequence={isBlicking} />
      </View> 

      <View style={{ flex: 2, flexDirection: "row" }}>
        <BartButton constantColor="#0B5351" color="#0B5351" title="Sequence 1" onPress={()=>sendRequest("seq1",true)} />
        <BartButton constantColor="#00A9A5" color="#00A9A5" title="Sequence 2" onPress={()=>sendRequest("seq2",true)} />
        <BartButton constantColor="#007991" color="#007991" title="Sequence 3" onPress={()=>sendRequest("seq3",true)} />
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
  floating: {
    width: "80%",
    height: 200,
    position: "absolute",
    bottom: 50,
    left: 0,
    right: 0
  }
});
