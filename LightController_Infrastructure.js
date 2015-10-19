/*
	@author James Vorderbruggen
*/
var serialport = require('serialport'),
    plotly = require('plotly')('JamesVorder','zc13lq6791');


var data = [{x:[], y:[], stream:{token:'1syhxdj4x0', maxpoints:1000}}];
var graphOptions = {"fileopt" : "overwrite", "filename" : "proximity-test", style : {"type" : "scatter"}};


var portName = 'COM3';
var sp = new serialport.SerialPort(portName,{
    baudRate: 9600,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false,
    parser: serialport.parsers.readline("\r\n")
});

plotly.plot(data,graphOptions,function(err, msg) {
  var stream = plotly.stream('1syhxdj4x0', function (err, msg) {
  	if(err){ return console.log("ERROR", err); }
    console.log(msg);
  });

  var i = 0;
  sp.on('data', function(input) {
  		if(isNaN(input) || input > 1023) return;
	    var streamObject = JSON.stringify({ x : i, y : input });
	    console.log(streamObject);
	    stream.write(streamObject+"\n");
	    i++;
	});
});
