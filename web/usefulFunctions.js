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
