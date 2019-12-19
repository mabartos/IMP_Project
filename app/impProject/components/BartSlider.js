import React from 'react';
import { StyleSheet, View, Text } from 'react-native';

import { Slider } from 'react-native-elements';

const BartSlider = ({onChange}) => {
    const [sliderValue, setSliderValue] = React.useState(50);

    const style = StyleSheet.create({
        root: {
            alignItems: "center",
            justifyContent: "center",
            flex: 1,
            padding: 3
        },
        slider: {
            height: "90%",
        },
        text:{
            textAlign: "center",
            color: "#0075A2",
            fontWeight:"bold",
            fontSize: 20,
        },
        minimumValue: 0,
        maximumValue: 100,
        step: 1,
        value: sliderValue,
    });

    const valueChanged = (value) => {
        setSliderValue(value);
        onChange(value);
    }

    return (
        <View style={style.root}>
            <Text style={style.text}>{style.value} %</Text>
            <Slider style={style.slider}
                maximumValue={style.maximumValue}
                minimumValue={style.minimumValue}
                step={style.step}
                orientation="vertical"
                value={style.value}
                onValueChange={valueChanged}
                thumbStyle={{backgroundColor:"black",width:60,height:30}}
            />
        </View>
    );
}

export default BartSlider;