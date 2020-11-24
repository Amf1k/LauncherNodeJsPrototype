var {Launcher, hello} = require('bindings')('LauncherNodeJsPrototype');
const EventEmitter = require('events').EventEmitter
const inherits = require('util').inherits
const emitter = new EventEmitter()
const l = new Launcher();

emitter.on('inGameTimeChanged', (time) => {
    console.log(time)
});
l.callAndEmit(emitter.emit.bind(emitter));
console.log(l.games())
l.startGame();
console.log(hello()); // 'world'

l.exec();

