import React from 'react';
import { StyleSheet, View ,Text} from 'react-native';

import { Slider } from 'react-native-elements';

const BartSlider = (color) => {
    const [sliderValue,setSliderValue]=React.useState(50);

    const style = StyleSheet.create({
        root: {
            alignItems: "center",
            justifyContent: "center",
            flex: 1,
            padding:3
        },
        slider: {
            height: "90%",
        },
        minimumValue: 0,
        maximumValue: 100,
        step: 1,
        value: sliderValue,
    });

    return (
        <View style={style.root}>
            <Text>{style.value} %</Text>
            <Slider style={style.slider}
                maximumValue={style.maximumValue}
                minimumValue={style.minimumValue}
                step={style.step}
                orientation="vertical"
                value={style.value}
                onValueChange={setSliderValue}
            />
        </View>
    );
}

export default BartSlider;