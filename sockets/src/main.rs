// Socket Programming Practice
use std::{
    io::{prelude::*, BufReader},
    net::{TcpListener, TcpStream},
};

fn main() {
    // We bind to a certain port.
    // There could be an error when binding to a port (like unauthorized access).
    let listener = TcpListener::bind("127.0.0.1:7878").unwrap();

    // Streams are connections
    // Incoming listens for every connection attempt
    for stream in listener.incoming() {
        // There could be a connection error like limits.
        let stream = stream.unwrap();

        //  For every new connection we get three responses because
        // of TCP three way handshakes.
        // println!("Connection established!");
        handle_connection(stream);
    }

    println!("Hello, world!");
}

fn handle_connection(mut stream: TcpStream) {
    let buf_reader = BufReader::new(&mut stream);
    let http_request: Vec<_> = buf_reader
        .lines()
        .map(|result| result.unwrap())
        .take_while(|line| !line.is_empty())
        .collect();

    // We print the requests
    // println!("Request {:#?}", http_request);
    
    let response = "HTTP/1.1 200 OK\r\n\r\n";

    // TCP Streams only handle bytes
    stream.write_all(response.as_bytes()).unwrap();
}