//%attributes = {}
$version:=wraycam Get version 

$devices:=wraycam Get devices 

$status:=wraycam Open ("";"wraycam_event_m";"{}")

If ($status.success)
	
	wraycam Close ($status.id)
	
End if 