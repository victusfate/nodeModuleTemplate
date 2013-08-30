var moduleName = require('../build/Release/moduleName.node');
var MyObject = moduleName.MyObject;
var moduleLib = require('../lib/ModuleName')

var world = "World";
console.log("c binding interface "+moduleName.hello(world));

console.log("lib interface "+moduleLib.hello(world));
  
var obj = new MyObject(10);
console.log( '11', obj.plusOne() ); // 11
console.log( '12', obj.plusOne() ); // 12
console.log( '13', obj.plusOne() ); // 13