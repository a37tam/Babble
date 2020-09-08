## Babble
Babble is a cross-platform instant messaging app which lets users communicate using text messages.

​                                 

![combined-image](/home/alan/Desktop/combined-image.png)



## Description

Babble is modelled after the **client-server architecture**. This lets multiple users communicate in a group chat. 

Text messages are written to and read from TCP sockets. By using the **TCP/IP protocol**, Babble ensures the reliable transmission of text messages between the clients and server without any loss of data.



## Dependencies

Install standalone Boost.Asio, Qt, and CMake.



## Running Babble

If you would like to run both the clients and server **locally**, run the shell script **runBabbleLocally.sh**.

If you would like to run the client and server on **separate computers**, edit your **hosts and services file** to accept incoming TCP connection requests on port 9999 of the server.