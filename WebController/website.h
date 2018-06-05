const char webpage[] PROGMEM=
"<!DOCTYPE html>"
"<html>"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
"<head>"
"<style>"
"* {box-sizing: border-box}"
"body, html {"
    "height: 100%;"
    "margin: 0;"
    "font-family: Arial;"
"}"
".btn{"
    "background-color: #37342D;"
	"border-style: solid;"
    "border: 20px;"
    "border-radius: 20%;"
	"border-color: red;"
    "color: white;"
    "padding: 10px 10px;"
    "text-align: center;"
    "text-decoration: none;"
    "display: inline-block;"
    "font-size: 16px;"
    "margin: 0px 0px;"
    "cursor: pointer;"
    "width: 100%;"
"}"
".btn:hover{"
    "background-color: #357c38;"
"}"
".tablink {"
    "background-color: #003019;"
    "color: white;"
    "float: left;"
    "border: none;"
    "outline: none;"
    "cursor: pointer;"
    "padding: 14px 16px;"
    "font-size: 16px;"
    "width: 100%;"
"}"
".tablink:hover {"
    "background-color: #05FB03;"
"}"
".tabcontent {"
    "background-color: #ababab;"
    "alignment-baseline: central;"
    "color: 'black';"
    "border: none;"
    "display: none;"
	"margin: none;"
    "padding: 100px 20px;"
    "height: 100%;"
"}"
"table{"
    "margin: auto;"
"}"
"#bar{"
    "background-color: #41984C;"
    "margin: none;"
    "border: 0px;"
    "border-spacing: none;"
    "border-collapse: collapse;"
    "padding: none;"
    "width:100%;"
"}"
"</style>"
"</head>"
"<body>"
"<table id=\"bar\">"
    "<td><button class=\"tablink\" id = \"DefaultOpen\" onclick=\"openPage('Helm', this, '#05FB03')\">Helm</button></td>"
    "<td><button class=\"tablink\" onclick=\"openPage('DVD', this, '#05FB03')\">Nav</button></td>"
    "<td><button class=\"tablink\" onclick=\"openPage('ATV', this, '#05FB03')\">Weapons</button></td>"
    "<td><button class=\"tablink\" onclick=\"openPage('OTHER', this, '#05FB03')\">Other</button></td>"
"</table>"
"<div id=\"Helm\" class=\"tabcontent\">"
  "<table>"
    "<tr>"
        "<td><button id=\"burn\" class=\"btn\" >Burn</button></td>"
    "</tr>"
  "</table>"
"</div>"
"<div id=\"DVD\" class=\"tabcontent\">"
  "<table>"
    "<tr>"
        "<td colspan=\"3\"> <button id=\"DV-PW\" class=\"btn\">Power</button> </td>"
    "</tr>"
  "</table>"
"</div>"
"<div id=\"ATV\" class=\"tabcontent\">"
  "<table>"
    "<tr>"
        "<td> <button id=\"AT-MN\" class=\"btn\">Menu</button> </td>"
        "<td> <button id=\"AT-UP\" class=\"btn\">UP</button></td>"
        "<td> <button id=\"AT-BK\" class=\"btn\">Back</button> </td>"
    "</tr>"
	"</table>"
"</div>"
"<div id=\"OTHER\" class=\"tabcontent\">"
  "<h3>OTHER Stuff</h3>"
  "<p>HELLO GJPSPIASDPNASPdn</p>"
"</div>"
"<script>"
    "function openPage(pageName,elmnt,color) {"
        "var i, tabcontent, tablinks;"
        "tabcontent = document.getElementsByClassName(\"tabcontent\");"
        "for (i = 0; i < tabcontent.length; i++) {"
            "tabcontent[i].style.display = \"none\";"
        "}"
        "tablinks = document.getElementsByClassName(\"tablink\");"
        "for (i = 0; i < tablinks.length; i++) {"
            "tablinks[i].style.backgroundColor = \"\";"
        "}"
        "document.getElementById(pageName).style.display = \"block\";"
        "elmnt.style.backgroundColor = color;"
    "}"
    "document.getElementById(\"DefaultOpen\").click();"
    "function sendCommand(cmd) {"
        "var xml = new XMLHttpRequest();"
        "var req = \"com=\"+cmd;"
        "xml.open('post', '/postUrl');"
		"xml.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');"
        "xml.send(req);"
    "}"
	"var ids = ['burn'];"
	"ids.forEach(function(item,index,array){document.getElementById(item).onclick = function(){sendCommand(item)}});"
"</script>"  
"</body>"
"</html>";

