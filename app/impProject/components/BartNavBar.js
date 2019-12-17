import React from 'react';
import { Text, View,StyleSheet} from 'react-native';

const BartNavBar = () => {

    const Style=StyleSheet.create({
        root:{
            flex:1,
            flexDirection:"row",
            backgroundColor:"#0075A2",
            width:"100%",
            alignItems: "center",
            justifyContent: "flex-start",
            paddingLeft:10
        },
        text:{
            alignItems: "flex-start",
             justifyContent: "flex-start" ,
             color:"white",
             fontSize:20
        }
    });

    return (
        <View style={Style.root}>
            <Text style={Style.text}>
                Bartos LED Controller
        </Text>
        </View>
    );
}

export default BartNavBar;