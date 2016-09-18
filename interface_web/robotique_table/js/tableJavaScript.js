 var positionPoint = [];

 var coordX = 0;
 var coordY = 0;

 var ladate;
 var sansReponseSomme = 0;

 var scrollAuto = true;

 var requeteBoucle;
 var URL = "http://192.168.1.50/test_coord_ros.php";

var canvas;
var context;


 function initialisationCanvas() { // méthode permettant d'initialiser le canvas 
	if(canvas == null){
		canvas = document.getElementById('canvas_table'); // Permet de pointer la balise avec l'id myCanvas
    	context = canvas.getContext('2d'); 
    }
    context.clearRect(0, 0, canvas.width, canvas.height); 
    grille();
    rectangle_base();
  }

function departVert(){
	initialisationCanvas();
	ajoutPointRobot(30,220);
}

function departViolet(){
	initialisationCanvas();
	ajoutPointRobot(570,220);
}

function grille(){
	for(var i=0;i<600;i= i + 20){
		if(i<400){
					traceTraitGrille(i,0,i,400)
		}
		traceTraitGrille(0,i,600,i)
		traceTraitGrille(i,0,i,400)		
	}
}

function rectangle_base(){
	context.fillStyle = "#33CC00";
	context.fillRect(0,160,60,120);
	context.fillStyle = "#9933ff";
	context.fillRect(540,160,60,120);
}

function traceTraitGrille(Xdeb,Ydeb,Xfin,Yfin){
	context.beginPath();
	context.moveTo(Xdeb,Ydeb); 
	context.lineTo(Xfin,Yfin);
	context.lineWidth=2;
	context.strokeStyle = '#EEEEEE';
	context.stroke();
	context.closePath();
}

function traceTraitInterPoint(Xdeb,Ydeb,Xfin,Yfin){
	context.beginPath();
	context.moveTo(Xdeb,Ydeb); 
	context.lineTo(Xfin,Yfin);
	context.strokeStyle = '#b3d1ff';
	context.lineWidth=4;
	context.stroke();
	context.closePath();
}

function ajoutPointRobot(x,y){
	context.fillStyle = "#0066ff";
	context.fillRect(x,y,10,10);
	positionPoint.push([x,y]);
	if(positionPoint.length > 1){
		indexAvant = positionPoint.length - 2;
		traceTraitInterPoint(positionPoint[indexAvant][0],positionPoint[indexAvant][1],x,y);
	}
}

function clickAjoutAlea(){
	do{
	x = (Math.floor ( Math.random() * 3 ) - 1)*20;
	y = (Math.floor ( Math.random() * 3 ) - 1)*20;
	indexAvant = positionPoint.length - 1;
	console.log(indexAvant);
	newX = positionPoint[indexAvant][0] + x;
	newY = positionPoint[indexAvant][1] + y;
	}while((newY < 0 || newY > 400) || (newX < 0 || newX > 600));
	ajoutPointRobot(newX,newY);
}

function getMousePos(evt) {
    var rect = canvas.getBoundingClientRect();
    return {
      x: evt.clientX - rect.left,
      y: evt.clientY - rect.top
    };
}

function draw(e){
	var pos = getMousePos(e);
	posx = pos.x;
	posy = pos.y;
	ajoutPointRobot(posx,posy);
}

function rechercheDonne(){
	$.get(URL, function( my_var ) {
    ajoutPoisitionRequeteHTTP(my_var);}, 'html');
}

function returnDateFull(){
	ladate = new Date();
	return (ladate.getHours()+":"+ladate.getMinutes()+":"+ladate.getSeconds()+":"+ladate.getMilliseconds());
}


function ajoutPoisitionRequeteHTTP(data){
 	console.log(data)
	tabPosition = data.split(";");
	if(tabPosition[0] != coordX || tabPosition[1] != coordY){
		coordX = tabPosition[0];
		coordY = tabPosition[1];
		ajoutPointRobot(tabPosition[0]/5,tabPosition[1]/5);
		var objDiv = document.getElementById("log");
		objDiv.innerHTML += "<p> <font color='#8AFF63'>"+returnDateFull()+" #LOG POSITION# - <b>"+coordX+" : "+coordY+"<br>";
		if(scrollAuto){
			objDiv.scrollTop = objDiv.scrollHeight;	
		} 
		sansReponseSomme = 0;
	}else{
		sansReponseSomme++;
	}

	if(sansReponseSomme > 10){
		sansReponseSomme = 0;
		var objDiv = document.getElementById("log");
		objDiv.innerHTML += "<p> <font color='#CC3300'>"+returnDateFull()+" #LOG POSITION# - <b> Position inchangée !!!!<br>";
		if(scrollAuto){
			objDiv.scrollTop = objDiv.scrollHeight;	
		} 
	}

 	
}


function legendeBegin(){
	initialisationCanvas();
    context.font = "20pt Calibri,Geneva,Arial";
    context.strokeStyle = "#FF0000";
    context.strokeText("Sélectionne une zone de départ",100,200);
}


function clickScrollAuto(){
	scrollAuto = !scrollAuto;
	if(scrollAuto){
		document.getElementById("clickScroll").innerHTML = "SCROLL MANU";
	}else{
		document.getElementById("clickScroll").innerHTML = "SCROLL AUTO";
	}
}

function lancerRequete(){
	if(positionPoint.length > 0){
		document.getElementById("log").innerHTML += "<p><font color='blue'> Requete HTTP LANCEE !! "+URL+"<br>";
		requeteBoucle = setInterval(rechercheDonne,200);
	}else{
		document.getElementById("log").innerHTML += "<p><font color='red'> SELECTIONNE UNE ZONE !!!!!! <br>";
	}
}

function clearCanvas(){
	legendeBegin();
	positionPoint = [];
	if(requeteBoucle != null){
		stopRequete();
	}
}



function stopRequete(){
	document.getElementById("log").innerHTML += "<p><font color='blue'> Requete HTTP STOPPEE !! "+URL+"<br>";
	clearInterval(requeteBoucle);
}
