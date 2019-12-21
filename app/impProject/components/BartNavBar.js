/**
 *  Martin Bartos (xbarto96)
 *  Custom Navigation Bar
 *  Original (Last modified : 21.12.2019)
 */

import React from 'react';
import { Text, View, StyleSheet } from 'react-native';

const BartNavBar = (title) => {

    // CSS Style
    const Style = StyleSheet.create({
        root: {
            flex: 1,
            flexDirection: "row",
            backgroundColor: "#0075A2",
            width: "100%",
            alignItems: "center",
            justifyContent: "flex-start",
            paddingLeft: 10
        },
        text: {
            alignItems: "flex-start",
            justifyContent: "flex-start",
            color: "white",
            fontSize: 20
        }
    });

    return (
        <View style={Style.root}>
            <Text style={Style.text}>
                {title}
        </Text>
        </View>
    );
}

export default BartNavBar;