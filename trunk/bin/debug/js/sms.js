// JavaScript Document
$("document").ready(function(){
	$("#btn_search").blur(function(){
		$("#message").find("span").each(function(index,element){
			var tmp = $(this).html();
			//tmp = tmp.replace(new RegExp("<BR>",'g'), "");
			tmp  = tmp.replace(new RegExp("<FONT color=red>",'g'), "");
			tmp  = tmp.replace(new RegExp("</FONT>",'g'), "");
			//alert(tmp);
			var input_text = $("#btn_search").val();
			tmp = tmp.replace(new RegExp(input_text,'g'), "<FONT color=red>" + input_text + "</FONT>");
			
			$(this).html(tmp);
		});
	});	
	
	$("#txt_message_content").focus(function() {
		if ($(this).val() == '回复：') {
			$(this).html("");
		}
	});
	$("#txt_message_content").blur(function() {
		if($(this).val() == "") {
			$(this).html("回复：");	
		}
	});
	
	$("#btn_eliminate").click(function() {
		$("#txt_message_content").html("");	
		$("#txt_message_content").focus();
		$("#btn_send_message").addClass('btn_send_message').removeClass('btn_send_message_on');
	});
	
	$("#txt_message_content").keyup(function() {
		if ($(this).val() != "") {
			$("#btn_send_message").addClass('btn_send_message_on').removeClass('btn_send_message');
		} 
		if ($(this).val() == "") {
			
			$("#btn_send_message").addClass('btn_send_message').removeClass('btn_send_message_on');
		}
	});
	
	//新建短信
	$("#btn_message_new").click(function() {
		ban();
		var iHeight = ($(window).height()-($(this).height()+200))/2;

		$("#createMessage").css("left", iWidth);
		$("#createMessage").css("top", iHeight);
		$("#createMessage").show();	
	});
	
	$("#btn_close").click(function() {
		$("#createMessage").hide();	
		document.body.removeChild(bgObj);	
	});
	
	$("#btn_close").mousemove(function() {
		$(this)[0].src = "images/close_on.png";	
	});
	$("#btn_close").mouseout(function() {
		$(this)[0].src = "images/close_off.png";	
	});
	
	$("#btn_cancel").click(function() {
		$("#createMessage").hide();	
		document.body.removeChild(bgObj);
	});
	
	//导入短信
	
	$("#btn_message_import").click(function() {
		ban();
		var iHeight = ($(window).height()-($(this).height()+200))/2;
		$("#message_import").css("left", iWidth);
		$("#message_import").css("top", iHeight);
		$("#message_import").show();	
	});
	
	$("#btn_import_close").click(function() {
		$("#message_import").hide();
		document.body.removeChild(bgObj);	
	});
	
	$("#btn_import_close").mouseover(function() {
		$(this)[0].src="images/close_on.png";
	});
	$("#btn_import_close").mouseout(function() {
		$(this)[0].src="images/close_off.png";
	});
	
	//短信导出
	$("#btn_message_export").click(function() {
		ban();
		var iHeight = ($(window).height()-($(this).height()+200))/2;
		$("#message_export").css("left", iWidth);
		$("#message_export").css("top", iHeight);
		$("#message_export").show();
	});
	
	$("#btn_export_close").click(function() {
		$("#message_export").hide();
		document.body.removeChild(bgObj);	
	});
	$("#btn_export_close").mouseover(function() {
		$(this)[0].src="images/close_on.png";
	});
	$("#btn_export_close").mouseout(function() {
		$(this)[0].src="images/close_off.png";
	});
	
	//发送短信
	$("#btn_send_message").click(function() {
		var message = $("#txt_message_content").val();
		i_message.window.showMessage(message);
		$("#txt_message_content").html("");
		$("#txt_message_content").focus();
		$("#btn_send_message").addClass('btn_send_message').removeClass('btn_send_message_on');
		i_message.document.body.scrollTop=i_message.document.body.scrollHeight;
	
	});
	/*$("#btn_send_message").mouseover(function() {
		if ($("txt_message_content").val == "回复：" ) {
			$("#btn_send_message").addClass('btn_send_message_off').removeClass('btn_send_message_on');
		}
	});
	$("#btn_send_message").mouseout(function() {
		if ($("txt_message_content").val == "回复：") {
			$("#btn_send_message").addClass('btn_send_message_on').removeClass('btn_send_message_off');
		}
	});*/
	
	//
	$("#btn_select_pc").click(function(){
		openFile();
	});
	
	//刷新
	$("#btn_message_reload").mouseover(function() {
		$("#btn_message_reload").addClass('btn_message_reload_on').removeClass('btn_message_reload');	
	});
	$("#btn_message_reload").mouseout(function() {
		$("#btn_message_reload").addClass('btn_message_reload').removeClass('btn_message_reload_on');	
	});
	
	//选择联系人
	$("#btn_icon_contacts").click(function() {
		 var iHeight = ($(window).height()-($(this).height()+220))/2;
		 $("#frm_contact_choose").css("left", iWidth);
		 $("#frm_contact_choose").css("top", iHeight);
		 $("#frm_contact_choose").show();
	});
});

function close_Contact_Choose() {
	$("#frm_contact_choose").hide();	
}

function openFile() {
	var openfile = document.getElementById("openFile");
	openfile.click();
	alert(openfile.value);
}

function saveFile() {
	var fd = new ActiveXObject("MSComDlg.CommonDialog");
	   
	fd.Filter = "*.*";
	fd.FilterIndex = 2;
	// must setting
	fd.MaxFileSize = 128;
	var path = fd.SaveOpen();
	alert(path.value);
	       
}

