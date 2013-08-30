isNode = typeof module isnt 'undefined' and module.exports

if (isNode) 
    moduleName    = require('../build/Release/moduleName.node')

    

ModuleName = () ->

module.exports = ModuleName if isNode
    
ModuleName.hello = (world) ->
    moduleName.hello(world)

