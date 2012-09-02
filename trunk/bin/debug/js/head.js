// JavaScript Document
function fnClose()
{
	// 关闭主窗口
	if(bIsCustomBrowser)
	{
		window.external.CB_Close();
		
	}
}

$(document).ready(function(){
	//移动窗体
  	$("#move").mousedown(function(e) {
    	
		window.external.CPP_MoveMainDlg(e.pageX, e.pageY);
  	});
	
	//移动窗体
  	$("#move1").mousedown(function(e) {
    	    	
		window.external.CPP_MoveMainDlg(e.pageX, e.pageY);
  	});
	
	//关闭win窗体
	$("#btn_win_close").click(function() {
		$(this)[0].src="images/close_on.png";	
		fnClose();
	});
	
	$("#btn_win_close").mouseout(function() {
		$(this)[0].src="images/close_off.png";	
	});
	$("#btn_win_close").mouseover(function() {
		$(this)[0].src="images/close_over.png";	
	});
	
	
	//最小化窗体
	$("#btn_win_min").click(function() {
		$(this)[0].src="images/min_on.png";	
		window.external.CPP_Min();
	});
	
	$("#btn_win_min").mouseout(function() {
		$(this)[0].src="images/min_off.png";	
	});
	$("#btn_win_min").mouseover(function() {
		$(this)[0].src="images/min_over.png";	
	});
	
	/*菜单事件*/
	$("#menu_message").click(function(){
		location.href="sms.html";  	
	});
	
	$("#menu_contacts_off").click(function(){
		location.href="contact.html";
	});
	
	$("#menu_home_off").click(function() {
		location.href="Custom.html";	
	});
	
	$("#menu_download_shop_off").click(function() {
		location.href="mm_download.html";	
	});
});