/**
 *  Martin Bartos (xbarto96)
 *  Main component of project
 *  Original (Last modified : 21.12.2019)
 */

import React, { useEffect } from 'react';
import { StyleSheet, View } from 'react-native';
import BartButton from './components/BartButton';
import BartNavBar from './components/BartNavBar';
import BartSlider from './components/BartSlider';
import BartModal from './components/BartModal';

export default function App() {  
  const serverURL = "http://192.168.66.66:8282/";
  const BLICKING_ENDPOINT = "blicking";
  const FADING_ENDPOINT = "fading";

  // Defining states by Hooks
  const [response, setResponse] = React.useState(null);
  const [error, setError] = React.useState(null);
  const [sequenceName, setSequenceName] = React.useState("none");
  const [modalVisible, setModalVisible] = React.useState(false);

  const [modalConnectVisible, setModalConnect] = React.useState(false);
  const [modalConnectText,setModalConnectText]=React.useState("");

  const [isBlicking, setBlicking] = React.useState(false);
  const [isFading, setFading] = React.useState(false);

  // Request, if the server is successfuly set up
  const connectModal=()=>{
    fetch(`${serverURL}/connect`)
    .then(response => {
      setModalConnect(true);
      if(response.status===200)
        setModalConnectText("Connection to AP was Successful")
      else
        setModalConnectText("Connection to AP was Unsuccessful")
    })
    .catch((error)=>{
      setModalConnect(true);
      setError(error);
      setModalConnectText("Connection to AP was Unsuccessful")
    });
  }

  // Before first render of component. Show modal, if it's successfuly connected, or not.
  useEffect(() => {
    connectModal();
  }, []);

  // Request for change intensity of lights
  const changeIntensity = (path) => (value) => {
    fetch(`${serverURL}${path}?intensity=${value}`)
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

  // Set state of lights. Either 'true' or 'false'.
  const setState = (expectedEndpoint, actualEndpoint, requiredState, func) => {
    if (expectedEndpoint === actualEndpoint) {
      requiredState ? func(true) : func(false);
    }
  };

  // Send general request. ShowModal is flag, which determines displaying modal.
  const sendRequest = (endpoint, showModal) => {
    if (showModal) {
      setSequenceName(endpoint);
      setModalVisible(true);
    }
    fetch(serverURL + endpoint)
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

  // Request for change state of lights.
  const changeState = (path, isSequence) => (isActive) => {
    const stateMessage = isActive ? "off" : "on";
    setSequenceName(path);

    setState(BLICKING_ENDPOINT, path, !isActive, setBlicking);
    setState(FADING_ENDPOINT, path, !isActive, setFading);

    if ((isSequence || isBlicking || isFading) && !isActive) {
      setModalVisible(true);
    }
    var endpoint = path + "?state=" + stateMessage;
    sendRequest(endpoint);
  }

  return (
    <View style={styles.container}>
      <BartNavBar title="Bartos LED Controller" />
      <BartModal visible={modalConnectVisible} showText={modalConnectText} onClose={() => setModalConnect(false)}></BartModal>
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
        <BartButton constantColor="#0B5351" color="#0B5351" title="Sequence 1" onPress={() => sendRequest("seq1", true)} />
        <BartButton constantColor="#00A9A5" color="#00A9A5" title="Sequence 2" onPress={() => sendRequest("seq2", true)} />
        <BartButton constantColor="#007991" color="#007991" title="Sequence 3" onPress={() => sendRequest("seq3", true)} />
      </View>
    </View>
  );
}

// CSS styles
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
