import React, { Component } from 'react';
import { Text, TouchableOpacity, StyleSheet } from 'react-native';

const MyButton = ({ onPress, title, color }) => {

    const [isActive, setActive] = React.useState(false);
    const [buttonColor, setButtonColor] = React.useState('transparent');

    const onClick = () => {
        isActive ? setButtonColor('transparent') : setButtonColor(color);
        setActive(!isActive);
        onPress();
    }

    const ButtonStyle = StyleSheet.create({
        root: {
            alignItems: "center",
            justifyContent: "center",
            flex: 1,
            backgroundColor: buttonColor,
            alignItems: 'center',
            margin: 3,
            borderRadius: 10,
            borderWidth: 0.2
        },
        text: {
            color: 'black'
        }
    });

    return (<TouchableOpacity onPress={onClick} style={ButtonStyle.root}>
        <Text style={ButtonStyle.text}>{title}</Text>
    </TouchableOpacity>
    );


}

export default MyButton