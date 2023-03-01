//https://onlineconvertfree.com/convert-format/jpg-to-html/
void append_page_header() {
//  webpage  = F("<!DOCTYPE html lang='tr'><html>");
  webpage  = F("<!DOCTYPE html ><html>");
  webpage += F("<head>");
  webpage += F("<title>Densi File Server</title>"); // NOTE: 1em = 16px
  webpage += F("<meta http-equiv='content-type' content='text/html; charset=iso-8859-9' />");
  webpage += F("<meta charset='UTF-8'>");
  webpage += F("<meta name='viewport' content='user-scalable=yes,initial-scale=1.0,width=device-width'>");
  webpage += F("<script>function c(l){document.getElementById('s').value=l.getAttribute('data-ssid')||l.innerText||l.textContent;p = l.nextElementSibling.classList.contains('l');document.getElementById('p').disabled = !p;if(p)document.getElementById('p').focus();};function f() {var x = document.getElementById('p');x.type==='password'?x.type='text':x.type='password';}</script> ");
  webpage += F("<style>");
  webpage += F("body{max-width:65%;margin:0 auto;font-family:arial;font-size:105%;text-align:center;color:blue;background-color:#F7F2Fd;}");
  webpage += F("ul{list-style-type:none;margin:0.1em;padding:0;border-radius:0.375em;overflow:hidden;background-color:#dcade6;font-size:1em;}");
  webpage += F("li{float:left;border-radius:0.375em;border-right:0.06em solid #bbb;}last-child {border-right:none;font-size:85%}");
  webpage += F("li a{display: block;border-radius:0.375em;padding:0.44em 0.44em;text-decoration:none;font-size:85%}");
  webpage += F("li a:hover{background-color:#EAE3EA;border-radius:0.375em;font-size:85%}");
  webpage += F("section {font-size:0.88em;}");
  webpage += F("h1{color:white;border-radius:0.5em;font-size:1em;padding:0.2em 0.2em;background:#558ED5;}");
  webpage += F("h2{color:orange;font-size:1.0em;}");
  webpage += F("h3{font-size:0.8em;}");
  webpage += F("table{font-family:arial,sans-serif;font-size:0.9em;border-collapse:collapse;width:85%;}"); 
  webpage += F("th,td {border:0.06em solid #dddddd;text-align:left;padding:0.3em;border-bottom:0.06em solid #dddddd;}"); 
  webpage += F("tr:nth-child(odd) {background-color:#eeeeee;}");
  webpage += F(".rcorners_n {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:20%;color:white;font-size:75%;}");
  webpage += F(".rcorners_m {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:50%;color:white;font-size:75%;}");
  webpage += F(".rcorners_w {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:70%;color:white;font-size:75%;}");
  webpage += F(".column{float:left;width:50%;height:45%;}");
  webpage += F(".row:after{content:'';display:table;clear:both;}");
  webpage += F("*{box-sizing:border-box;}");
  webpage += F("footer{background-color:#eedfff; text-align:center;padding:0.3em 0.3em;border-radius:0.375em;font-size:60%;}");
  webpage += F("button{border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:25%;color:white;font-size:130%;}");
  webpage += F(".buttons {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:15%;color:white;font-size:80%;}");
  webpage += F(".buttonsm{border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:9%; color:white;font-size:70%;}");
  webpage += F(".buttonm {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:15%;color:white;font-size:70%;}");
  webpage += F(".buttonw {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:40%;color:white;font-size:70%;}");
  webpage += F("a{font-size:75%;}");
  webpage += F("p{font-size:75%;}");
  webpage += F("input{text-align:right;}");
  webpage += F("select{text-align:left; width:175px; }");

  webpage += F(".q{height:16px;margin:0;padding:0 5px;text-align:right;min-width:38px;float:right}");
  webpage += F(".q.q-0:after{background-position-x:0}.q.q-1:after{background-position-x:-16px}.q.q-2:after{background-position-x:-32px}.q.q-3:after{background-position-x:-48px}.q.q-4:after{background-position-x:-64px}.q.l:before{background-position-x:-80px;padding-right:5px}.ql .q{float:left}.q:after,.q:before{content:'';width:16px;height:16px;display:inline-block;background-repeat:no-repeat;background-position: 16px 0;");
  webpage += F("background-image:url('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGAAAAAQCAMAAADeZIrLAAAAJFBMVEX///8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADHJj5lAAAAC3RSTlMAIjN3iJmqu8zd7vF8pzcAAABsSURBVHja7Y1BCsAwCASNSVo3/v+/BUEiXnIoXkoX5jAQMxTHzK9cVSnvDxwD8bFx8PhZ9q8FmghXBhqA1faxk92PsxvRc2CCCFdhQCbRkLoAQ3q/wWUBqG35ZxtVzW4Ed6LngPyBU2CobdIDQ5oPWI5nCUwAAAAASUVORK5CYII=');}");
  webpage += F("@media (-webkit-min-device-pixel-ratio: 2),(min-resolution: 192dpi){.q:before,");
  webpage += F(".q:after {background-image:url('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAALwAAAAgCAMAAACfM+KhAAAALVBMVEX///8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADAOrOgAAAADnRSTlMAESIzRGZ3iJmqu8zd7gKjCLQAAACmSURBVHgB7dDBCoMwEEXRmKlVY3L//3NLhyzqIqSUggy8uxnhCR5Mo8xLt+14aZ7wwgsvvPA/ofv9+44334UXXngvb6XsFhO/VoC2RsSv9J7x8BnYLW+AjT56ud/uePMdb7IP8Bsc/e7h8Cfk912ghsNXWPpDC4hvN+D1560A1QPORyh84VKLjjdvfPFm++i9EWq0348XXnjhhT+4dIbCW+WjZim9AKk4UZMnnCEuAAAAAElFTkSuQmCC');");
  webpage += F("background-size: 95px 16px;}}");

  webpage += F("</style></head><body><h1>File Server Ver:"); webpage += String(ServerVersion) + "</h1>";
  //webpage += F("<img src='/Logo_Densi_H136x180.png' alt='Densi Logo'/>");
  webpage += "<img src='data:image/png;base64,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' alt='Densi Image'/>";
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void append_page_footer(){ // Saves repeating many lines of code for HTML page footers
  webpage += F("</br><a href='/'>[Back]</a><br><br>");
  webpage += F("<ul>");
  webpage += F("<li><a href='/'>Home</a></li>"); // Lower Menu bar command entries
#if defined(FULL)  
  webpage += F("<li><a href='/dir'>Directory</a></li>");
  webpage += F("<li><a href='/download'>Download</a></li>"); 
  webpage += F("<li><a href='/upload'>Upload</a></li>"); 
  webpage += F("<li><a href='/label'>Label</a></li>");
  webpage += F("<li><a href='/plu'>Plu</a></li>");
#endif    
  webpage += F("<li><a href='/parametre'>Parametre</a></li>"); 
  webpage += F("<li><a href='/wifisetting'>Wifi Setting</a></li>"); 
  webpage += F("<li><a href='/update'>Update Firmware</a></li>");
  webpage += F("<li><a href='/factorymod'>Factory Mod</a></li>"); 
  webpage += F("<li><a href='/espreset'>Reset</a></li>"); 
  webpage += F("</ul>");
  webpage += "<footer>Densi Endüstriye Tartı Sistemleri </footer>";
  webpage += "</footer>";
  // webpage += "<footer>&copy;"+String(char(byte(0x40>>1)))+String(char(byte(0x201>>1)))+String(char(byte(0x5c>>1)))+String(char(byte(0x98>>1)))+String(char(byte(0x5c>>1)));
  // webpage += String(char((0x84>>1)))+String(char(byte(0xd2>>1)))+String(char(0xe4>>1))+String(char(0xc8>>1))+String(char(byte(0x40>>1)));
  // webpage += String(char(byte(0x64/2)))+String(char(byte(0x60>>1)))+String(char(byte(0x62>>1)))+String(char(0x70>>1))+"</footer>";
  webpage += "</body></html>";
}
