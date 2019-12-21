/**
 *  Martin Bartos (xbarto96)
 *  Custom Button
 *  Original (Last modified : 21.12.2019)
 */

import React from 'react';
import { Text, TouchableOpacity, StyleSheet, View } from 'react-native';

const BartButton = ({ onPress, title, color, sequence, isLight, constantColor }) => {
    const defaultColor = constantColor ? constantColor : "#dddddd";
    const [isActive, setActive] = React.useState(false);
    const [buttonColor, setButtonColor] = React.useState(defaultColor);

    // Event onClick, which determines the activation of specific buttons.
    const onClick = () => {
        if (isActive || !sequence || isLight) {
            isActive ? setButtonColor(defaultColor) : (!sequence) ? setButtonColor(color) : setButtonColor(defaultColor);
            !sequence ? setActive(!isActive) : null;
            onPress(isActive);
        } else {
            if (!sequence)
                setButtonColor(color);
        }
    }

    // CSS Style
    const ButtonStyle = StyleSheet.create({
        root: {
            alignItems: "center",
            justifyContent: "center",
            flex: 1,
            margin: 3,
            borderRadius: 10,
            borderWidth: 0.2,
        },
        text: {
            color: 'black',
            fontSize: 20,
            flex: 2,
            marginTop: 30,
            textAlign: "center",
            alignItems: "center",
            justifyContent: "center",
        },
        underline: {
            flex: 1,
            width: "100%",
            backgroundColor: buttonColor,
            borderBottomLeftRadius: 10,
            borderBottomRightRadius: 10
        }
    });

    return (
        <TouchableOpacity onPress={onClick} style={ButtonStyle.root}>
            <Text style={ButtonStyle.text}>{title}</Text>
            <View style={ButtonStyle.underline} />
        </TouchableOpacity>
    );
}

export default BartButton