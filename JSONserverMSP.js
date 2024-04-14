// Routes readSensors  message to serial port and sends back reply

const express =require("express");
const app = express();
const http = require('http').Server(app);
const io = require('socket.io')(http);

const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');

const port =  new SerialPort({ path: 'COM4', baudRate: 9600 }, function (err) {
  if (err) {
    return console.log('Error on port open: ', err.message);
  }
  console.log('Serial Port Open');
});
const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }));

let activeClients = 0;  //number of connected clients

app.get('/', function(req, res){
  res.sendFile(__dirname + '/index.html');
});


io.on('connection', function(socket){
	//update the client count on the webpage
  socket.on('disconnect', function(){
    activeClients -=1; 
	io.emit('nClientUpdate', {clients:activeClients});
  });
  
  //print to the command prompt when actions are taken on the webpage
  socket.on('EmpChange',function(){
	port.write('EmpChange\n', function(err) {
      if (err) {
        return console.log('Error on port write: ', err.message);
      }
      console.log('Employee details changed, Showing new pallet');
    });
  });
  socket.on('PalletChange',function(){

	port.write('PalletChange\n', function(err) {
      if (err) {
        return console.log('Error on port write: ', err.message);
      }
      console.log('Pallet ID changed by employee');
    });
  });
  socket.on('LogNote',function(){

	port.write('LogNote\n', function(err) {
      if (err) {
        return console.log('Error on port write: ', err.message);
      }
      console.log('Employee added a note to the log');
    });
  });
  socket.on('LogPrint',function(){

	port.write('LogPrint\n', function(err) {
      if (err) {
        return console.log('Error on port write: ', err.message);
      }
      console.log('Log was printed');
    });
  });
  socket.on('LogDownloaded',function(){

	port.write('LogDownloaded\n', function(err) {
      if (err) {
        return console.log('Error on port write: ', err.message);
      }
      console.log('Log downloaded as a text file');
    });
  });
  

  activeClients +=1;
  io.emit('nClientUpdate', {clients:activeClients});
});




//Data handler for data received from Serialport via parser
parser.on('data', function(data) {
	let dataStr = data.toString();
    console.log(dataStr);
	if(dataStr.startsWith('Sensors=')){ //accelerometer readings
    //extract JSON object after 'Sensors='
		let data = JSON.parse(dataStr.substring('Sensors='.length));
		io.emit('sensorReadings', data);
	}
	if (dataStr === 'Button Pressed') { //hardware button
        io.emit('buttonReading', {message: 'Button Pressed!'});
	}
});

port.on('close', function() {
  console.log('Port closed');
})

port.on('error', function(err) {
  console.log('Error on port: ', err.message);
})

http.listen(4000, function(){
  console.log('listening on *:4000');
});

