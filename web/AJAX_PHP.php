<!--page.php-->
<!DOCTYPE HTML> 
<html lang="zh-cn">
<head>
<title>MyPHP</title>
<meta charset="utf-8" />
<script>
function show(str){
	if(str.length==0){
		document.getElementById("txtint").innerHTML="";
		return;
	}
	var xh=GetXMLHttpObject();
	if(xh==null){
		alert("Browser does not support HTTP Request!");
		return;
	}
	xh.onreadystatechange=function(){
		if(xh.readyState==4 && xh.status==200){
			document.getElementById("txtint").innerHTML=xh.responseText;
		}
	}
	xh.open("GET","/server.php?txt="+str,true);
	xh.send(null);
}
function GetXMLHttpObject(){
	var xmlHttp=null;
	try{
		/Firefox, Opera 8.0+, Safari
		xmlHttp=new XMLHttpRequest();
	}catch(e){
		try{
			//IE 6+
			xmlHttp=new ActiveObject("Msxml2.XMLHTTP");
		}catch(e){
			//IE 5.5
			xmlHttp=new ActiveObject("Microsoft.XMLHTTP");
		}
	}
	return xmlHttp;
}
</script>
</head>
<body>

<input type="text" onkeyup="show(this.value)" /><br />
<b>Response Text: </b>
<p id="txtint"><p>

</body>
</html>

<!--server.php-->
<?php
echo $_GET["txt"];
?>
