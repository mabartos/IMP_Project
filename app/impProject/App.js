import React from 'react';
import { StyleSheet, View, Button, Text } from 'react-native';
import MyButton from './components/MyButton';
import BartNavBar from './components/BartNavBar';
import BartSlider from './components/BartSlider';

export default function App() {

  const [response, setResponse] = React.useState(null);
  const [error, setError] = React.useState(null);
  const [isSequence, setSequence] = React.useState(false);


  const changeIntensity = (path) => (value)=>{
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

  const changeState = (path) => (isActive) => {
    console.log(isActive)
    const stateMessage = isActive ? "off" : "on";
    fetch(`http://192.168.0.179:8282/${path}?state=${stateMessage}`)
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

  return (
    <View style={styles.container}>
      <BartNavBar />

      <View style={{ flex: 2, flexDirection: "row" }}>

        <MyButton onPress={changeState("red")} color="#FF5964" title="RED" />
        <MyButton onPress={changeState("green")} color="#6BF178" title="Green" />
        <MyButton onPress={changeState("blue")} color="#35A7FF" title="Blue" />
      </View>

      <View style={{ flex: 4, flexDirection: "row" }}>
        <BartSlider onChange={changeIntensity("red")}/>
        <BartSlider onChange={changeIntensity("green")}/>
        <BartSlider onChange={changeIntensity("blue")}/>
      </View>

      <View style={{ flex: 2, flexDirection: "row" }}>
        <MyButton color="green" title="R" sequence={isSequence} />
        <MyButton color="yellow" title="R" sequence={isSequence} />
        <MyButton color="pink" title="R" sequence={isSequence} />
      </View>

      <View style={{ flex: 2, flexDirection: "row" }}>
        <MyButton onPress={changeState("blicking")} color="blue" title="Blicking" />
        <MyButton onPress={changeState("fading")} color="yellow" title="Fading" />
      </View>

      {
        response && <View style={styles.floating}>
          <Text>{response.message} {response.status}</Text>
        </View>
      }
      {
        /* error && <View>
          <Text>{error} </Text>
        </View> */
      }
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
