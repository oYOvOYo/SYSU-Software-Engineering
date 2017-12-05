---
layout:     post
title:      "JavaScript-Study"
date:       2017-02-10
updated:     2017/02/28
tags:
    - Web
    - JavaScript
categories:
    - Study
---

JavaScript的相关知识

# Learning Advanced Javascript

## Reference

[Website](http://ejohn.org/apps/learn/)

## Content

bind()

```javascript
// The .bind method from Prototype.js 
Function.prototype.bind = function(){ 
  var fn = this, args = Array.prototype.slice.call(arguments), object = args.shift(); 
  return function(){ 
    return fn.apply(object, 
      args.concat(Array.prototype.slice.call(arguments))); 
  }; 
};
```

callee()

```javascript
var ninja = { 
  yell: function(n){ 
    return n > 0 ? arguments.callee(n-1) + "a" : "hiy"; 
  } 
}; 
assert( ninja.yell(4) == "hiyaaaa", "arguments.callee is the function itself." );
```

catch()

```javascript
function getElements( name ) { 
  var results; 
 
  if ( getElements.cache[name] ) { 
    results = getElements.cache[name]; 
  } else { 
    results = document.getElementsByTagName(name); 
    getElements.cache[name] = results; 
  } 
 
  return results; 
} 
getElements.cache = {}; 
 
log( "Elements found: ", getElements("pre").length ); 
log( "Cache found: ", getElements.cache.pre.length );
```

null

```javascript
// false
undefined === null
// true
undefined == null
```

context

```javascript
function katana(){ 
  this.isSharp = true; 
} 
katana(); 
assert( isSharp === true, "A global object now exists with that name and value." ); 
 
var shuriken = { 
  toss: function(){ 
    this.isSharp = true; 
  } 
}; 
shuriken.toss(); 
assert( shuriken.isSharp === true, "When it's an object property, the value is set within the object." );

var object = {};
function fn(){
  return this;
}
assert( fn() == this, "The context is the global object." );
assert( fn.apply(object) == object, "The context is changed to a specific object." );

function add(a, b){
  return a + b;
}
assert( add.call(this, 1, 2) == 3, ".call() takes individual arguments" );
assert( add.apply(this, [1, 2]) == 3, ".apply() takes an array of arguments" );
```

instantiation

```javascript
function User(first, last){ 
  // Make sure the new operator is always used
  if ( !(this instanceof arguements.callee()) ) 
    return new User(first, last); 
   
  this.name = first + " " + last; 
} 
 
var name = "Resig"; 
var user = User("John", name); 
 
assert( user, "This was defined correctly, even if it was by mistake." ); 
assert( name == "Resig", "The right name was maintained." );
```

flexible arguments 

```javascript
// merage
function merge(root){ 
  for ( var i = 1; i < arguments.length; i++ ) 
    for ( var key in arguments[i] ) 
      root[key] = arguments[i][key]; 
  return root; 
} 
 
var merged = merge({name: "John"}, {city: "Boston"}); 
assert( merged.name == "John", "The original name is intact." ); 
assert( merged.city == "Boston", "And the city has been copied over." );

// find min / max 
function smallest(){ 
  return Math.min.apply( Math, arguments ); 
} 
function largest(){ 
  return Math.max.apply( Math, arguments ); 
} 
assert(smallest(0, 1, 2, 3) == 0, "Locate the smallest value."); 
assert(largest(0, 1, 2, 3) == 3, "Locate the largest value.");

// make a Array
function highest(){ 
  return makeArray(arguments).sort(function(a,b){ 
    return b - a; 
  }); 
} 
 
function makeArray(array){ 
  return Array().slice.call( array ); 
} 
 
assert(highest(1, 1, 2, 3)[0] == 3, "Get the highest value."); 
assert(highest(3, 1, 2, 3, 4, 5)[1] == 4, "Verify the results.");

// magic success

function multiMax(multi){ 
  // Make an array of all but the first argument 
  var allButFirst = Array().slice.call( arguments, 1 ); 
 
  // Find the largest number in that array of arguments 
  var largestAllButFirst = Math.max.apply( Math, allButFirst ); 
 
  // Return the multiplied result 
  return multi * largestAllButFirst; 
} 
assert( multiMax(3, 1, 2, 3) == 9, "3*3=9 (First arg, by largest.)" );
```

closures

```javascript
var count = 0; 
 
var timer = setInterval(function(){ 
  if ( count < 5 ) { 
    log( "Timer call: ", count ); 
    count++; 
  } else { 
    assert( count == 5, "Count came via a closure, accessed each step." ); 
    assert( timer, "The timer reference is also via a closure." ); 
    clearInterval( timer ); 
  } 
}, 100);

(function(){ 
  var myLib = window.myLib = function(){ 
    // Initialize 
  }; 
 
  // ... 
})();

var myLib = (function(){ 
  function myLib(){ 
    // Initialize 
  } 
 
  // ... 
   
  return myLib; 
})();
```

prototype

```javascript
function Ninja(){ 
  this.swung = true; 
} 
 
var ninjaA = new Ninja(); 
var ninjaB = new Ninja(); 
 
Ninja.prototype.swingSword = function(){ 
  return this.swung; 
}; 
//  Prototyped properties affect all objects of the same constructor, simultaneously, even if they already exist.
assert( ninjaA.swingSword(), "Method exists, even out of order." ); 
assert( ninjaB.swingSword(), "and on all instantiated objects." );
```

instance type

```javascript
function Ninja(){} 
 
var ninja = new Ninja(); 
 
assert( typeof ninja == "object", "However the type of the instance is still an object." );   
assert( ninja instanceof Ninja, "The object was instantiated properly." ); 
assert( ninja.constructor == Ninja, "The ninja object was created by the Ninja function." );

// constructor
```

inheritance

````javascript
function Person(){}
Person.prototype.dance = function(){};

function Ninja(){}

// Achieve similar, but non-inheritable, results
Ninja.prototype = Person.prototype;
Ninja.prototype = { dance: Person.prototype.dance };

assert( (new Ninja()) instanceof Person, "Will fail with bad prototype chain." );

// Only this maintains the prototype chain
Ninja.prototype = new Person();

var ninja = new Ninja();
assert( ninja instanceof Ninja, "ninja receives functionality from the Ninja prototype" );
assert( ninja instanceof Person, "... and the Person prototype" );
assert( ninja instanceof Object, "... and the Object prototype" );
````

built-in Prototypes

```javascript
if (!Array.prototype.forEach) { 
  Array.prototype.forEach = function(fn){ 
    for ( var i = 0; i < this.length; i++ ) { 
      fn( this[i], i, this ); 
    } 
  }; 
} 

// Beware: Extending prototypes can be dangerous.c
delete Object.prototype.keys;
```

enforcing function context

```javascript
function bind(context, name){ 
  return function(){ 
    return context[name].apply(context, arguments); 
  }; 
} 
 
var Button = { 
  click: function(){ 
    this.clicked = true; 
  } 
}; 
 
var elem = document.createElement("li"); 
elem.innerHTML = "Click me!"; 
elem.onclick = bind(Button, "click"); 
document.getElementById("results").appendChild(elem); 
 
elem.onclick(); 
assert( Button.clicked, "The clicked property was correctly set on the object" );

// bind 
Function.prototype.bind = function(){ 
  var fn = this, args = Array.prototype.slice.call(arguments), object = args.shift(); 
  return function(){ 
    return fn.apply(object, 
      args.concat(Array.prototype.slice.call(arguments))); 
  }; 
}; 
 
var Button = { 
  click: function(value){ 
    this.clicked = value; 
  } 
}; 
 
var elem = document.createElement("li"); 
elem.innerHTML = "Click me!"; 
elem.onclick = Button.click.bind(Button, false); 
document.getElementById("results").appendChild(elem); 
 
elem.onclick(); 
assert( Button.clicked === false, "The clicked property was correctly set on the object" )
```

function length

```javascript
function addMethod(object, name, fn){ 
  // Save a reference to the old method 
  var old = object[ name ]; 
 
  // Overwrite the method with our new one 
  object[ name ] = function(){ 
    // Check the number of incoming arguments, 
    // compared to our overloaded function 
    if ( fn.length == arguments.length ) 
      // If there was a match, run the function 
      return fn.apply( this, arguments ); 
 
    // Otherwise, fallback to the old method 
    else if ( typeof old === "function" ) 
      return old.apply( this, arguments ); 
  }; 
} 
```

