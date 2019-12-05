$status:=wraycam Start (Form:C1466.device.id)

If ($status.success)
	
	OBJECT SET ENABLED:C1123(*;"wraycam Open";False:C215)
	OBJECT SET ENABLED:C1123(*;"wraycam Start";False:C215)
	OBJECT SET ENABLED:C1123(*;"wraycam Stop";True:C214)
	OBJECT SET ENABLED:C1123(*;"wraycam Pause";True:C214)
	OBJECT SET ENABLED:C1123(*;"wraycam Close";True:C214)
	
End if 