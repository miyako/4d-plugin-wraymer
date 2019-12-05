//%attributes = {}
C_LONGINT:C283($1;$event)
C_TEXT:C284($2)

C_OBJECT:C1216($params)

$event:=$1
$params:=JSON Parse:C1218($2;Is object:K8:27)

Case of 
	: ($event=WRAYCAM_EVENT_IMAGE)
		
		$status:=wraycam Get image ($params.device.id;WRAYCAM_IMAGE)
		CALL FORM:C1391($params.window;$params.method;$status)
		
	: ($event=WRAYCAM_EVENT_STILLIMAGE)
		
		$status:=wraycam Get image ($params.device.id;WRAYCAM_STILL_IMAGE)
		CALL FORM:C1391($params.window;$params.method;$status)
		
End case 