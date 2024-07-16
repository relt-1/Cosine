type (ML620909) 
extrn code : _main
public $$start_up

CSEG AT 0:0H
DW 0F000H
DW $$start_up
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt
DW _rt

$$start_up:
	b _main

_rt:
	rti
