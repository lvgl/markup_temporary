# lv_obj

## Properties
- width
  - type: size
  - help: "The width of the object"    
- height
  - type: size
  - help: "The height of the object"
- x
  - type: position
  - help: "The x coordinate of the widget. If align is set then the offset from the align position."
- y
  - type: psoition
  - help: "The y coordinate of the widget. If align is set then the offset from the align position."
- align: 
  - values: `LV_ALIGN_CENTER`, `LV_ALIGN_TOP_LEFT`, etc
  - help: "Where to align the object on its parent. x and y are relative to the alignemnt."
- flags
  - type: obj_flag 
  - values: * (means all)
  - help: "Turn on/off features of the obejcts"
- state
  - type: state  
  - values: *
  - help: "Set the the current state of the object"
- parts:
  - type: part 
  - values: `LV_PART_MAIN`, `LV_PART_SCROLLBAR`   

## size
- units
  - px
  - %
  - LV_SIZE_CONTENT
- min: -8000
- max: 8000  

## position
- units
  - px
  - %
- min: -8000
- max: 8000  

## obj_flag
- HIDDEN
  - help: "Make on object hidden"
- SCROLLABLE
  - help "Make an object scrollable"
...

