<%@page pageEncoding="UTF-8"%>
<%@ page import="net.violet.platform.util.StaticTools" %>
<%@ page import="net.violet.platform.util.SessionTools" %>
<% response.setContentType("text/html;charset=UTF-8"); %>

<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html" %>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean" %>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic" %>
<%@ include file="/include_jsp/utils/inc_dico.jsp" %>


<%	String dico_lang =	Long.toString(SessionTools.getLangFromSession(session, request).getId());%>

&nbsp;

<script type="text/javascript">
	var obj = parent;
	var framed = true;
	
	//console.debug("obj.msg_txt > "+obj.msg_txt);

  	if (top.location == self.document.location) {
		obj = window;
		framed = false;  	
  	}
  		
	//console.debug("obj > "+obj);
	//console.debug("framed > "+framed);
		
	var msg = "";
	var col = obj.gErrorColor;
	
	<logic:equal name="myMessagesSendMp3Form" property="erreur" value="parental_error">
		msg = obj.msg_txt['parental_error'];	
	</logic:equal>
		
	<logic:equal name="myMessagesSendMp3Form" property="erreur" value="no_id_rabbit">
		msg = obj.msg_txt['no_id_rabbit'];	
	</logic:equal>
	
	<logic:equal name="myMessagesSendMp3Form" property="erreur" value="create_tts_error">
		msg = obj.msg_txt['create_tts_error'];	
	</logic:equal>
	
	<logic:equal name="myMessagesSendMp3Form" property="erreur" value="send_tts_error">
		msg = obj.msg_txt['send_tts_error'];	
	</logic:equal>
	
	<logic:equal name="myMessagesSendMp3Form" property="erreur" value="no_credit_error">
		msg = obj.msg_txt['no_credit_error']; 	
	</logic:equal>
	
	<logic:equal name="myMessagesSendMp3Form" property="erreur" value="bad_rabbit_error">
		msg = obj.msg_txt['bad_rabbit_error'];	
	</logic:equal>
	
	<logic:equal name="myMessagesSendMp3Form" property="erreur" value="black_list_error">
		msg = obj.msg_txt['black_list_error']; 	
	</logic:equal>
	
	<logic:equal name="myMessagesSendMp3Form" property="erreur" value="server_error">
		msg = obj.msg_txt['server_error'];	
	</logic:equal>
	
	<logic:equal name="myMessagesSendMp3Form" property="erreur" value="OK">
		msg = obj.msg_txt['msg_OK'];
		col = obj.gHColor;			
	</logic:equal>

	obj.showFormWaitForResponse("sendMsg", false);
	
	if (msg=="") msg = '<bean:write name="myMessagesSendMp3Form" property="erreur" />';
	
	
	var d = obj.document.getElementById("Messages_mp3");
	var id = "";
	var _home = "";
	
	if (d!=null) id = "Messages_mp3";
	else {
		id = "QuickNabSmenu";
		_home = "Home";
	}
	

	// on ferme le "envoyer plus tard"
	obj.messagesDateToggle("force_close");
	
	obj.$("div.mainTabBody").msgPopup(msg, col, 4000);	

	//obj.alertWaitActionResponse( msg );
	
	<logic:equal name="myMessagesSendMp3Form" property="erreur" value="OK">
		//obj.messagesEndMp3upload(id, '../action/myMessages'+_home+'Mp3.do');
		obj.$("#musicName").val("");
		obj.$("#musicFile").val("");
		/*obj.$("#idMp3").select_SelectFromValue("");*/
	</logic:equal>
	
	if (!framed) obj.tabMessageChangeUrl( id, '../action/myMessages'+_home+'Mp3.do');
	
</script>
