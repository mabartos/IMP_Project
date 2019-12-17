import React from 'react';
import { StyleSheet, View,Button} from 'react-native';
import MyButton from './components/MyButton';
import BartNavBar from './components/BartNavBar';
import BartSlider from './components/BartSlider';

export default function App() {

  const [response, setResponse] = React.useState(null)
  const [error, setError] = React.useState(null)
  const [isSequence,setSequence]=React.useState(false);
  const [clicked,setClicked]=React.useState(false);

  const buttonClicked = (path) => {
    fetch(`http://192.168.0.179:8282/${path}`)
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
      <View style={{ height: 24 }}>
      </View>

      <BartNavBar />

      <View style={{ flex: 2, flexDirection: "row" }}>

       <MyButton onPress={() => buttonClicked("red")} color="#FF5964" title="RED" />
        <MyButton onPress={() => buttonClicked("green")} color="#6BF178" title="Green" />
        <MyButton onPress={() => buttonClicked("blue")} color="#35A7FF" title="Blue" />
      </View>

      <View style={{ flex: 4, flexDirection: "row" }}>
        {/* <BartSlider />
        <BartSlider />
        <BartSlider /> */}
      </View>

      <View style={{ flex: 2, flexDirection: "row" }}>
        <MyButton color="green" title="R" sequence={isSequence}/>
        <MyButton color="yellow" title="R" sequence={isSequence}/>
        <MyButton color="pink" title="R" sequence={isSequence}/>
      </View>

      <View style={{ flex: 2, flexDirection: "row" }}>
        <MyButton color="blue" title="R" />
        <MyButton color="yellow" title="R" />
        <MyButton color="blue" title="R" />

      </View>

       {
       /*  response && <View style={styles.floating}>
          <Text>{response.message} {response.status}</Text>
        </View> */
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
