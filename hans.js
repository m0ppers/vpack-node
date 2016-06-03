var vpackNode = require('./');

var buf = vpackNode.encode({"ha": 1, "lu": [1,6.1,"ha"], "hasi": "hoho"});

console.log(vpackNode.decode(buf));
