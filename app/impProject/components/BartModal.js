import React from 'react';
import { Modal, View, Alert, Text, StyleSheet, TouchableHighlight } from 'react-native';

const BartModal = ({ visible, nameOfSequence, onClose }) => {

    const modalStyle = StyleSheet.create({
        rootView: {
            backgroundColor: "black",
            opacity: 0.6,
            height: "100%",
            top:0,
            zIndex:1,
        },
        notification: {
            position:"absolute",
            margin: 22,
            top: "20%",
            height: "30%",
            backgroundColor: "white",
            borderRadius: 4,
            borderWidth: 0.2,
            alignItems: 'center',
            justifyContent: 'center',
            zIndex:2
        },
        text: {
            textAlign: "center",
            color: "#0075A2",
            fontWeight:"bold",
            fontSize: 25,
            margin:10
        },
        cancelButton:{
            alignItems: 'center',
            justifyContent: 'center',
            borderWidth:0.2,
            width:"30%",
            height:"30%",
            margin:10
        }
    });

    return (
        <Modal
            animationType="slide"
            transparent={true}
            visible={visible}
            onRequestClose={() => {
                Alert.alert('Modal closed');
            }}
        >
            <View style={modalStyle.rootView}>
            </View>
            <View style={modalStyle.notification}>
                <Text style={modalStyle.text} >Wait for complete the sequence '{nameOfSequence}'</Text>
                <TouchableHighlight style={modalStyle.cancelButton} onPress={onClose} >
                    <Text style={modalStyle.text,{fontSize:15}}>Cancel</Text>
                </TouchableHighlight>
            </View>
            

        </Modal>
    );
}

export default BartModal;