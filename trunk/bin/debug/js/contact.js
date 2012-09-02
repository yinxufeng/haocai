// JavaScript Document
//日志
//var log = new Log(Log.DEBUG, Log.popupLogger);
var log = log4javascript.getDefaultLogger(); 

var contact_selectall_flag = true;
//全靠
function contact_selectall() {
	
	if (contact_selectall_flag) {
		$("#contacts_selectall")[0].src = "images/contacts/contacts_selectall_on.png";
		f_contact.window.checked();
		
		contact_selectall_flag = false;
		
	} else {
		$("#contacts_selectall")[0].src = "images/contacts/contacts_selectall_off.png";
		f_contact.window.unchecked();
		contact_selectall_flag=true;
		
	}
	
}





//关闭
function closeiframe() {
	$("#iframe1").hide();

}

//添加html
function addHtml(s) {
	$("#contact").html(s);	
	var checkflag = true;   //是否被选中
	$("input[name='checkbox2']").each(function(){
		_this = $(this);
		_this.click(function(){
			if(this.checked) {
				parent.contact_content($(this).val()); //设置联系人详情
				
				checkflag = false;
				$(this).attr("checked", true);  //设置复选框被选中
				
			} else {
				checkflag = false;
				
				$(this).attr("checked", false);   
			}
		});
	});
	$("#contact").each(function(index, element){
	
		$(this).find("div[class='contact_div2']").click(function(){
			if (checkflag) {
				$("input[name='checkbox2']").each(function(){this.checked=false;});
				$("#contact").find("div[class='contact_div2']").css("background-color","#F6FAFB");
				
				$(this).find("input").attr("checked", true);
			}
			if($(this).find("input").attr("checked") == true) {
				$(this).css("background-color","#FBE7AC");
				parent.contact_content($(this).find("input").attr("value"));
			} else {
				$(this).css("background-color","#F6FAFB");
			}
			
			checkflag = true;
		});	
	});	
}


//刷新联系人
function loadReferContacts(){
	if(bIsCustomBrowser) {
		window.external.CPP_OnRequestRfreshContactData();
	}
}

//加载联系人
function loadContact() {
	if(bIsCustomBrowser) {
		window.external.CPP_OnRequestContactData();
	}
	
	/*var fso, f1, ts, s="";  
    var ForReading = 1;  
    fso = new ActiveXObject("Scripting.FileSystemObject");  
    ts = fso.OpenTextFile("c:\\data.txt",   ForReading); 
    while (!ts.AtEndOfStream)  
        s+= ts.ReadLine(   );
    //alert(s);
    ts.Close();
	JS_OnRequestContactData(s);*/
	

}


//加载联系人
function JS_OnRequestContactData(_contact) {
	//alert(_contact);
	if (_contact != "") {
	var json_contact = _contact;
	var myE = eval(json_contact);
	var text = JSON.stringify(myE); 
	log.info(text);
	var object = JSON.parse(text);
	//var contact=object.person;
	var contact=object;
	
	var s="";
	for(var i =0;i<contact.length;i++)
	{
	   switch(contact[i].position){
		 case 'A':
		 	s+="<div class=\"contact_div1\">A</div>";
		 	break;
		 case 'B':
			s+="<div class=\"contact_div1\">B</div>";
			break;
		 case 'C':
			s+="<div class=\"contact_div1\">C</div>";
			break;
		 case 'D':
			s+="<div class=\"contact_div1\">D</div>";
			break;
		 case 'E':
		 	s+="<div class=\"contact_div1\">E</div>";
		 	break;
		 case 'F':
			s+="<div class=\"contact_div1\">F</div>";
			break;
		 case 'G':
			s+="<div class=\"contact_div1\">G</div>";
			break;
		 case 'H':
			s+="<div class=\"contact_div1\">H</div>";
			break;
		 case 'I':
		 	s+="<div class=\"contact_div1\">I</div>";
		 	break;
		 case 'J':
			s+="<div class=\"contact_div1\">B</div>";
			break;
		 case 'K':
			s+="<div class=\"contact_div1\">C</div>";
			break;
		 case 'L':
			s+="<div class=\"contact_div1\">D</div>";
			break;
		 case 'M':
		 	s+="<div class=\"contact_div1\">E</div>";
		 	break;
		 case 'N':
			s+="<div class=\"contact_div1\">F</div>";
			break;
		 case 'O':
			s+="<div class=\"contact_div1\">O</div>";
			break;
		 case 'P':
			s+="<div class=\"contact_div1\">P</div>";
			break;
		 case 'Q':
			s+="<div class=\"contact_div1\">Q</div>";
			break;
		 case 'R':
		 	s+="<div class=\"contact_div1\">R</div>";
		 	break;
		 case 'S':
			s+="<div class=\"contact_div1\">S</div>";
			break;
		 case 'T':
			s+="<div class=\"contact_div1\">T</div>";
			break;
		 case 'U':
			s+="<div class=\"contact_div1\">U</div>";
			break;
		 case 'V':
		 	s+="<div class=\"contact_div1\">V</div>";
		 	break;
		 case 'W':
			s+="<div class=\"contact_div1\">W</div>";
			break;
		 case 'X':
			s+="<div class=\"contact_div1\">X</div>";
			break;
		 case 'Y':
			s+="<div class=\"contact_div1\">Y</div>";
			break;
		case 'Z':
			s+="<div class=\"contact_div1\">Z</div>";
			break;
	   }
	   
	  /* s += "<div class='contact_div2' onselectstart=\"return false;\"><input type='checkbox' name='checkbox2' " +
	   "value=\"person:[{name:'"+contact[i].name+"',mobile:'"+contact[i].mobilenumber + "',mobilehome:" + contact[i].mobilehome 
	   + "mobilework"+ "',groupid:'" + contact[i].groupid+"'}]\">" 
	   + contact[i].name  + "<span id='moble'>"+contact[i].mobilenumber + "</span></div>";*/
	   
	    s += "<div class='contact_div2' onselectstart=\"return false;\"><input type='checkbox' name='checkbox2' " +
	   "value=\"person:[" + JSON.stringify(contact[i]).replace(new RegExp("\"",'g'), "\'") + "]\">" + contact[i].name  + "<span id='moble'>"+contact[i].mobilenumber + "</span></div>";
		//alert(s);
	}
	}
	
	f_contact.window.addHtml(s);
		
}

//进度条
function JS_ProgressBar(iWidth) {
	
	iframe1.window.go(iWidth);	
}



$(document).ready(function(){
		
	//导入
	$("#btn_contacts_import").click(function() {
		//$("#iframe1").show();
		//导入联系人，调用C++内置函数
		//window.external.CPP_Contacts_Import();
		ban();
		var iHeight = ($(window).height()-400)/2;
		$("#contact_import").css("left", iWidth);
		$("#contact_import").css("top", iHeight);
		$("#contact_import").show();
	});
	
	$("#btn_import_close").click(function(){
		$("#contact_import").hide();
		document.body.removeChild(bgObj);	
	});
	
	$("#btn_import_close").mouseover(function(){
		$(this)[0].src = "images/close_on.png";
	});
	$("#btn_import_close").mouseout(function(){
		$(this)[0].src = "images/close_off.png";
	});

	
	
	//新建联系人
	$("#contacts_new").click(function() {
		$("#contacts_new")[0].src="images/contacts/contacts_new_on.png";		
		$("#img_new_contact")[0].src="images/contacts/dialog_word_newly-build-contact.png";
		//清空所有的值
		$("#contact_id").html("");
		$("#contact_name").attr("value","");
		$("#contact_mobile").attr("value","");
		$("#contact_email").attr("value","");
		$("#contact_address").attr("value","");
		$("#contact_company").attr("value","");
		$("#contact_duties").attr("value","");
		$("#select_group").html("<option value='0'>未分组</option>");
		 //mask.style.visibility='visible';
		ban();
		var iWidth = ($(window).width()-500)/2;
		var iHeight = ($(window).height()-400)/2;
		$("#createContact").css("left", iWidth);
		$("#createContact").css("top", iHeight);
		$("#createContact").show();	
				
	});
	$("#contacts_new").mouseout(function() {
		$("#contacts_new")[0].src="images/contacts/contacts_new_off.png";								 
	});
	var bgObj;
	//禁止操作Body
	function ban() {
		 var iWidth = document.documentElement.clientWidth; 
		 var iHeight = document.documentElement.clientHeight; 
		 bgObj = document.createElement("div"); 
		 bgObj.style.cssText = "position:absolute;left:0px;top:0px;width:"+iWidth+"px;height:"+Math.max(document.body.clientHeight, iHeight)+"px;filter:Alpha(Opacity=60);opacity:0.3;background-color:#CCC;z-index:1;";
		 document.body.appendChild(bgObj); 
	}
	
	
	//新建分组
	$("#btn_newgroup").click(function() {
		$("#txt_newgroup").val("");
		$("#btn_newgroup").css('display','none');
		$("#txt_newgroup").css('display','block');	
		$("#txt_newgroup").focus();
		
		
		
	});
	
	//离开新建分组事件
	$("#txt_newgroup").blur(function(){
	   if($(this).val()!="") {
		   
		   $("#menu").append("<li><span>"+$(this).val()+"(0)</span></li>");
		   $("#menu").find("span").attr("class","memuSpan1");
		   //调用C++新建分组
		   if(bIsCustomBrowser) {JSON.stringify
			  var group = {group:[{"id":"","name":$(this).val(),"count":"","issystem":"1"}]};
			  //log.info(JSON.stringify(group));
		   	  window.external.CPP_OnRequestAddGroupData(JSON.stringify(group));
		   }
		   loadGroup();
		   //autoScorll();
	   }
	   
	   
	   $("#btn_newgroup").css('display','block');
	   $("#txt_newgroup").css('display','none');	
	});
	loadGroup();
	$("#menu").find("span").attr("class","memuSpan1");
	//加载分组
	function loadGroup() {
		 
		$("#menu").find("li").each(function(index, element) {
									
		var _this = $(this);
		
		_this.click(function(){	
			$("#menu").find("span").attr("class","memuSpan1");
			_this.find("span").attr("class","menuSpan");
		});
		});
	}
	
	
	
	
	//发送短信
	$("#btn_send_message").click(function() {
		$(this)[0].src="images/contacts/btn_send_message_on.png";									  
	});
	$("#btn_send_message").mouseover(function() {
		$(this)[0].src="images/contacts/btn_send_message_on.png";									  
	});
	$("#btn_send_message").mouseout(function() {
		$(this)[0].src="images/contacts/btn_send_message_off.png";									  
	});
	
	//编辑联系人
	$("#btn_edit_off").click(function() {
		$(this)[0].src="images/contacts/btn_edit_on.png";
		$("#img_new_contact")[0].src="images/contacts/dialog_edit-contact.png";
		f_contact.window.editContact();
		
		
		ban();
		var iWidth = ($(window).width()-500)/2;
		var iHeight = ($(window).height()-400)/2;
		$("#createContact").css("left", iWidth);
		$("#createContact").css("top", iHeight);
		$("#createContact").show();	
	});
	
	$("#btn_edit_off").mouseover(function() {
		$(this)[0].src="images/contacts/btn_edit_on.png";
	});
	$("#btn_edit_off").mouseout(function() {
		$(this)[0].src="images/contacts/btn_edit_off.png";
	});
	
	//刷新
	$("#contacts_reload").click(function(){
		$(this)[0].src="images/contacts/contacts_reload_on.png";									 
	});
	
	$("#contacts_reload").mouseout(function(){
		$(this)[0].src="images/contacts/contacts_reload_off.png";									 
	});
	
	//关闭按钮
	$("#btn_close").click(function() {
		$(this)[0].src="images/close_on.png";
		$("#createContact").hide();
		document.body.removeChild(bgObj);
	});
	$("#btn_close").mouseout(function(){
		$(this)[0].src="images/close_off.png";	
	});
	$("#btn_close").mouseover(function(){
		$(this)[0].src="images/close_over.png";	
	});
	
	//保存按钮
	$("#btn_save").click(function() {
		$(this)[0].src="images/contacts/dialog_preservation_on.png";
	});
	$("#btn_save").mouseout(function() {
		$(this)[0].src="images/contacts/dialog_preservation_off.png";
	});
	$("#btn_save").mouseover(function() {
		$(this)[0].src="images/contacts/dialog_preservation_over.png";
	});
	
	
	//取消按钮
	$("#btn_cancel").click(function() {
		$(this)[0].src="images/contacts/dialog_cancel_on.png";
		$("#createContact").hide();
		document.body.removeChild(bgObj);
	});
	$("#btn_cancel").mouseout(function() {
		$(this)[0].src="images/contacts/dialog_cancel_off.png";	
	});
	$("#btn_cancel").mouseover(function() {
		$(this)[0].src="images/contacts/dialog_cancel_over.png";	
	});
	
	
	
	//删除
	$("#contacts_delete").click(function() {
						
		f_contact.window.removeContact();
	});
	
	//导出联系人
	$("#contacts_export").click(function(){
		ban();
		var iHeight = ($(window).height()-($(this).height()+200))/2;
		$("#contact_export").css("left", iWidth);
		$("#contact_export").css("top", iHeight);
		$("#contact_export").show();
	});
	
	$("#btn_export_close").click(function() {
		$("#contact_export").hide();
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
		ban();
		var iHeight = ($(window).height()-($(this).height()+200))/2;

		$("#createMessage").css("left", iWidth);
		$("#createMessage").css("top", iHeight);
		$("#createMessage").show();		
	});
	
	//关闭发送短信窗体
	$("#btn_message_close").click(function() {
		$("#createMessage").hide();	
		document.body.removeChild(bgObj);	
	});
	
	$("#btn_message_close").mousemove(function() {
		$(this)[0].src = "images/close_on.png";	
	});
	$("#btn_message_close").mouseout(function() {
		$(this)[0].src = "images/close_off.png";	
	});
	
	//关闭发送短信窗体
	$("#btn_message_cancel").click(function() {
		$("#createMessage").hide();	
		document.body.removeChild(bgObj);
	});

	//选择联系人
	$("#btn_icon_contacts").click(function() {
		 var iHeight = ($(window).height()-($(this).height()+220))/2;
		 $("#frm_contact_choose").css("left", iWidth);
		 $("#frm_contact_choose").css("top", iHeight);
		 $("#frm_contact_choose").show();
	});
	
	//保存联系人
	$("#btn_save").click(function() {
		var id = $("#contact_id").html();
		log.info(id);
		saveContactsData(id);
		
	});
	
	//保存联系人信息
	function saveContactsData(id) {
		var name = $("#contact_name").attr("value");
		var group = $("#select_group").val();
		
		var mobilenumber = $("#contact_mobile").attr("value");
		var phone_type = $("#select_phone_type").val();
		var email = $("#contact_email").attr("value");
		var address = $("#contact_address").attr("value");
		var company = $("#contact_company").attr("value");
		var duties = $("#contact_duties").attr("value");
		
		
		var contact = {person:[{"id":id,"name":name,"groupid":[{group:""}],"mobilenumber":mobilenumber,"mobilehome":"","mobilework":"","phoneNumber":"","phonehome":"","phonework":"","email":email,"homeaddress":address, "company":company, "birthday":"", "fax":"", "departtment":"", "duties":duties, "pathtype":"0"}]};
		
		
		if(bIsCustomBrowser) {
			if(id == "") {
				window.external.CPP_OnRequestAddContactData(JSON.stringify(contact));
			} else {
				window.external.CPP_OnRequestEditContactData(JSON.stringify(contact));
			}
		}	
		log.info("保存联系人成功！");
		
		//隐藏窗体
		$("#createContact").hide();
		document.body.removeChild(bgObj);	
	}

});




//移除联系人
function removeContact() {
		var contacts = {type:"1",contactid:[{id:"123456"}]};	
		var flag = 0;
		var check_len = $("div[class='contact_div2']").length;
		$("div[class='contact_div2']").each(function(){
			var input = $(this).find("input");
			
			if (input.attr("checked") == true) {
				var id = eval(input.attr("value"))[0].id;
				alert(id);
				var contactid = {"id":id}
				if (flag == 0) {
					contacts = {contactid:[contactid]};
									
				} else {
					contacts.contactid.push(contactid);
				}
				flag++;
				$(this).remove();
			}
			
		});
		var delContacts = JSON.stringify(contacts);
		if (flag == check_len) {
			delContacts = JSON.stringify({"type":1});				
		}
		else if (flag == 1) {
			delContacts = delContacts.replace("{", "{\"type\":\"2\",");
		} else {
			delContacts = delContacts.replace("{", "{\"type\":\"3\",");
		}
			
		alert(delContacts);
		log.info(delContacts);
		
		if(bIsCustomBrowser) {
			window.external.CPP_OnRequestDeleteContactData(delContacts);
		}
		
}

//加载联系人详情
function editContact() {
	$("input[name='checkbox2']").each(function(){
			
		if (this.checked){
			parent.setEditContactData($(this).val());
			//alert($(this).val());
		}
	});	
}

//编辑联系人
function setEditContactData(Contact_Data) {
	var contact = eval(Contact_Data);
	
	//展示联系人联系人信息
	$("#contact_name").attr("value",contact[0].name);
	$("#select").html("<option>"+ contact[0].group + "</option>");
	$("#contact_mobile").attr("value", contact[0].mobilenumber);
	$("#contact_email").attr("value", contact[0].email);
	$("#contact_address").attr("value", contact[0].homeaddress);
	$("#contact_company").attr("value", contact[0].company);
	$("#contact_duties").attr("value", contact[0].duties);
	$("#contact_id").html(contact[0].id);
		
		
}

function checked(){
	$("input[name='checkbox2']").each(function(){this.checked=true;});
	$("#contact").find("div[class='contact_div2']").css("background-color","#FBE7AC");
}
function unchecked(){
	$("input[name='checkbox2']").each(function(){this.checked=false;});
	$("#contact").find("div[class='contact_div2']").css("background-color","#F6FAFB");
}

function contact_content(val) {
	
	var myE = eval(val);
	var text = JSON.stringify(myE); 
	var contact =JSON.parse(text); 
	$("#name").html(contact[0].name);
	var group = JSON.parse(JSON.stringify(eval(contact[0].groupid)));
	if (group.length > 0) {
		$("#group").html(group[0].group);
	} else {
		$("#group").html("");
	}
	$("#mobile").html(contact[0].mobilenumber);
	$("#email").html(contact[0].email);
	$("#address").html(contact[0].homeaddress);
	$("#company").html(contact[0].company);
	$("#job").html(contact[0].duties);
}


function close_Contact_Choose() {
	$("#frm_contact_choose").hide();	
}

//添加联系人回调函数
function JS_OnRequestAddContactFile(contact) {

	log.info(contact);	
}

//删除联系人回调函数
function JS_OnRequestDeleteContactData(BOOL) {
	log.info(BOOL);	
}

//编辑联系人回调函数
function JS_OnRequestEditContactData(BOOL) {
	log.info(BOOL);	
}

//添加分组
function JS_OnRequestAddGroupData( BOOL ){
	log.info(BOOL);
}

//请求分组
function JS_OnRequestGroupData(BOOL) {
	log.info(BOOL);
}


function loadGroups() {
	if(bIsCustomBrowser) {
		log.info("请求分组");
		window.external.CPP_OnRequestGroupData();
	}	
}