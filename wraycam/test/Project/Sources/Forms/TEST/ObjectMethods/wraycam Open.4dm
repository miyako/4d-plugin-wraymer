$params:=New object:C1471
$params.window:=Current form window:C827
$params.method:="wraycam_event_f"

C_COLLECTION:C1488($devices)
$devices:=wraycam Get devices 

If ($devices.length#0)
	
	C_OBJECT:C1216($device)
	$device:=$devices[0]
	$params.device:=$device
	
	$status:=wraycam Open ($device.id;"wraycam_event_m";JSON Stringify:C1217($params))
	
	If ($status.success)
		
		Form:C1466.device:=$device
		
		OBJECT SET ENABLED:C1123(*;"wraycam Open";False:C215)
		OBJECT SET ENABLED:C1123(*;"wraycam Start";True:C214)
		OBJECT SET ENABLED:C1123(*;"wraycam Stop";False:C215)
		OBJECT SET ENABLED:C1123(*;"wraycam Pause";False:C215)
		OBJECT SET ENABLED:C1123(*;"wraycam Close";True:C214)
		
	End if 
	
End if 