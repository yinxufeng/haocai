// JavaScript Document
function fnIsOurCustomBrowser()
{
	// 检验是否是自定义浏览器我们只用调用函数
	// CB_IsOurCustomBrowser看是否可以获得.
	// 不带()表示属性调用,可以检验函数是否在外部窗口
	// 返回null表示不是自定义窗口,返回false
	if(window.external.CB_IsOurCustomBrowser != null)
	{
		return true;
	}
	else
	{
		return false;
	}
}
	
// 用一个变量检验是否是自定义浏览器.
bIsCustomBrowser = fnIsOurCustomBrowser();

var bgObj;
	//禁止操作Body
function ban() {
	 var iWidth = document.documentElement.clientWidth; 
	 var iHeight = document.documentElement.clientHeight; 
	 bgObj = document.createElement("div"); 
	 bgObj.style.cssText = "position:absolute;left:0px;top:0px;width:"+iWidth+"px;height:"+Math.max(document.body.clientHeight, iHeight)+"px;filter:Alpha(Opacity=60);opacity:0.3;background-color:#CCC;z-index:1;";
	 document.body.appendChild(bgObj); 
}

var iWidth = ($(window).width()-500)/2;
var iHeight = ($(window).height()-400)/2;



