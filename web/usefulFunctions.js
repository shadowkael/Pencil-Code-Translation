//add function func() to window.onload events
function addLoadEvents(func){
    oldonload=window.onload;
    if(typeof(oldonload)!="function"){
        window.onload=func;
    }else{
        window.onload=function(){
            oldonload();
            func();
        }
    }
}
//insert newElement after targetElement
function insertAfter(newElement,targetElement){
	var p=targetElement.parentNode;
	if(p.lastChild==targetElement){
		p.appendChild(newElement);
	}else{
		p.insertBefore(newElement,targetElement.nextSibling);
	}	
}
//add an abbreviation dlist
function fun(){
	if(!document.createElement || !document.getElementsByTagName || !document.createTextNode) return false;
	var defs=new Array();
	var dlist=document.createElement("dl");
	var parent=document.getElementsByTagName("body")[0];
	var c=document.getElementsByTagName("abbr");
	for(var i=0;i<c.length;i++){
		var title=c[i].getAttribute("title");
		var key=c[i].lastChild.nodeValue;
		defs[key]=title;
	}
	for(key in defs){
		var dtitle=document.createElement("dt");
		var dtText=document.createTextNode(key);
		dtitle.appendChild(dtText);
		var ddesc=document.createElement("dd");
		var ddText=document.createTextNode(defs[key]);
		ddesc.appendChild(ddText);
		dlist.appendChild(dtitle);
		dlist.appendChild(ddesc);
	}
	parent.appendChild(dlist);
}

