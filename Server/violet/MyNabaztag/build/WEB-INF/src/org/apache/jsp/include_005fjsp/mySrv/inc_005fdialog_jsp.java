package org.apache.jsp.include_005fjsp.mySrv;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import net.violet.platform.datamodel.Application;
import net.violet.platform.util.StaticTools;
import net.violet.platform.util.SessionTools;
import net.violet.platform.datamodel.Lang;
import net.violet.platform.util.DicoTools;
import net.violet.platform.util.MyConstantes;
import net.violet.platform.datamodel.Application;

public final class inc_005fdialog_jsp extends org.apache.jasper.runtime.HttpJspBase
    implements org.apache.jasper.runtime.JspSourceDependent {

  private static java.util.List _jspx_dependants;

  static {
    _jspx_dependants = new java.util.ArrayList(1);
    _jspx_dependants.add("/include_jsp/utils/inc_dico.jsp");
  }

  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_bean_define_property_name_id_nobody;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_bean_define_type_property_name_id_nobody;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_logic_greaterThan_value_name;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_logic_notEmpty_property_name;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_logic_iterate_property_name_id;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_logic_lessEqual_value_name;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_logic_equal_value_name;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_html_form_styleId_styleClass_action;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_html_hidden_value_property_nobody;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_html_hidden_value_styleId_property_nobody;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_html_text_styleId_property_name_nobody;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_html_submit_value_styleClass_property_onclick;

  public Object getDependants() {
    return _jspx_dependants;
  }

  public void _jspInit() {
    _jspx_tagPool_bean_define_property_name_id_nobody = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_bean_define_type_property_name_id_nobody = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_logic_greaterThan_value_name = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_logic_notEmpty_property_name = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_logic_iterate_property_name_id = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_logic_lessEqual_value_name = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_logic_equal_value_name = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_html_form_styleId_styleClass_action = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_html_hidden_value_property_nobody = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_html_hidden_value_styleId_property_nobody = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_html_text_styleId_property_name_nobody = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_html_submit_value_styleClass_property_onclick = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
  }

  public void _jspDestroy() {
    _jspx_tagPool_bean_define_property_name_id_nobody.release();
    _jspx_tagPool_bean_define_type_property_name_id_nobody.release();
    _jspx_tagPool_logic_greaterThan_value_name.release();
    _jspx_tagPool_logic_notEmpty_property_name.release();
    _jspx_tagPool_logic_iterate_property_name_id.release();
    _jspx_tagPool_logic_lessEqual_value_name.release();
    _jspx_tagPool_logic_equal_value_name.release();
    _jspx_tagPool_html_form_styleId_styleClass_action.release();
    _jspx_tagPool_html_hidden_value_property_nobody.release();
    _jspx_tagPool_html_hidden_value_styleId_property_nobody.release();
    _jspx_tagPool_html_text_styleId_property_name_nobody.release();
    _jspx_tagPool_html_submit_value_styleClass_property_onclick.release();
  }

  public void _jspService(HttpServletRequest request, HttpServletResponse response)
        throws java.io.IOException, ServletException {

    JspFactory _jspxFactory = null;
    PageContext pageContext = null;
    HttpSession session = null;
    ServletContext application = null;
    ServletConfig config = null;
    JspWriter out = null;
    Object page = this;
    JspWriter _jspx_out = null;
    PageContext _jspx_page_context = null;


    try {
      _jspxFactory = JspFactory.getDefaultFactory();
      response.setContentType("text/html;charset=UTF-8");
      pageContext = _jspxFactory.getPageContext(this, request, response,
      			null, true, 8192, true);
      _jspx_page_context = pageContext;
      application = pageContext.getServletContext();
      config = pageContext.getServletConfig();
      session = pageContext.getSession();
      out = pageContext.getOut();
      _jspx_out = out;

      out.write("\n\n\r\n\r\n");
 response.setContentType("text/html;charset=UTF-8"); 
      out.write("\r\n\n\r\n\r\n\r\n\r\n");
      out.write('\n');
      out.write('\r');
      out.write('\n');
      out.write("\r\n\r\n\n");
	Lang dico_lang = SessionTools.getLangFromSession(session, request);
      out.write('\r');
      out.write('\n');
      out.write('\n');
      //  bean:define
      org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_0 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
      _jspx_th_bean_define_0.setPageContext(_jspx_page_context);
      _jspx_th_bean_define_0.setParent(null);
      _jspx_th_bean_define_0.setProperty("hasSomethingToDisplay");
      _jspx_th_bean_define_0.setName("mySrvDialogForm");
      _jspx_th_bean_define_0.setId("hasSomethingToDisplay");
      int _jspx_eval_bean_define_0 = _jspx_th_bean_define_0.doStartTag();
      if (_jspx_th_bean_define_0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
        _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_0);
        return;
      }
      _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_0);
      java.lang.Object hasSomethingToDisplay = null;
      hasSomethingToDisplay = (java.lang.Object) _jspx_page_context.findAttribute("hasSomethingToDisplay");
      out.write('\r');
      out.write('\n');
      //  bean:define
      org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_1 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
      _jspx_th_bean_define_1.setPageContext(_jspx_page_context);
      _jspx_th_bean_define_1.setParent(null);
      _jspx_th_bean_define_1.setProperty("isMarried");
      _jspx_th_bean_define_1.setName("mySrvDialogForm");
      _jspx_th_bean_define_1.setId("isMarried");
      int _jspx_eval_bean_define_1 = _jspx_th_bean_define_1.doStartTag();
      if (_jspx_th_bean_define_1.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
        _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_1);
        return;
      }
      _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_1);
      java.lang.Object isMarried = null;
      isMarried = (java.lang.Object) _jspx_page_context.findAttribute("isMarried");
      out.write('\r');
      out.write('\n');
      //  bean:define
      org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_2 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
      _jspx_th_bean_define_2.setPageContext(_jspx_page_context);
      _jspx_th_bean_define_2.setParent(null);
      _jspx_th_bean_define_2.setProperty("isWaiting");
      _jspx_th_bean_define_2.setName("mySrvDialogForm");
      _jspx_th_bean_define_2.setId("isWaiting");
      int _jspx_eval_bean_define_2 = _jspx_th_bean_define_2.doStartTag();
      if (_jspx_th_bean_define_2.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
        _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_2);
        return;
      }
      _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_2);
      java.lang.Object isWaiting = null;
      isWaiting = (java.lang.Object) _jspx_page_context.findAttribute("isWaiting");
      out.write('\r');
      out.write('\n');
      //  bean:define
      org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_3 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
      _jspx_th_bean_define_3.setPageContext(_jspx_page_context);
      _jspx_th_bean_define_3.setParent(null);
      _jspx_th_bean_define_3.setProperty("error_dne");
      _jspx_th_bean_define_3.setName("mySrvDialogForm");
      _jspx_th_bean_define_3.setId("error_dne");
      int _jspx_eval_bean_define_3 = _jspx_th_bean_define_3.doStartTag();
      if (_jspx_th_bean_define_3.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
        _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_3);
        return;
      }
      _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_3);
      java.lang.Object error_dne = null;
      error_dne = (java.lang.Object) _jspx_page_context.findAttribute("error_dne");
      out.write('\r');
      out.write('\n');
      //  bean:define
      org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_4 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
      _jspx_th_bean_define_4.setPageContext(_jspx_page_context);
      _jspx_th_bean_define_4.setParent(null);
      _jspx_th_bean_define_4.setProperty("error_same");
      _jspx_th_bean_define_4.setName("mySrvDialogForm");
      _jspx_th_bean_define_4.setId("error_same");
      int _jspx_eval_bean_define_4 = _jspx_th_bean_define_4.doStartTag();
      if (_jspx_th_bean_define_4.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
        _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_4);
        return;
      }
      _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_4);
      java.lang.Object error_same = null;
      error_same = (java.lang.Object) _jspx_page_context.findAttribute("error_same");
      out.write('\r');
      out.write('\n');
      //  bean:define
      org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_5 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_type_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
      _jspx_th_bean_define_5.setPageContext(_jspx_page_context);
      _jspx_th_bean_define_5.setParent(null);
      _jspx_th_bean_define_5.setProperty("serviceName");
      _jspx_th_bean_define_5.setName("mySrvDialogForm");
      _jspx_th_bean_define_5.setId("serviceName");
      _jspx_th_bean_define_5.setType("String");
      int _jspx_eval_bean_define_5 = _jspx_th_bean_define_5.doStartTag();
      if (_jspx_th_bean_define_5.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
        _jspx_tagPool_bean_define_type_property_name_id_nobody.reuse(_jspx_th_bean_define_5);
        return;
      }
      _jspx_tagPool_bean_define_type_property_name_id_nobody.reuse(_jspx_th_bean_define_5);
      String serviceName = null;
      serviceName = (String) _jspx_page_context.findAttribute("serviceName");
      out.write("\r\n\r\n<!-- Affichage des differentes Listes et demandes -->\r\n");
      //  logic:greaterThan
      org.apache.struts.taglib.logic.GreaterThanTag _jspx_th_logic_greaterThan_0 = (org.apache.struts.taglib.logic.GreaterThanTag) _jspx_tagPool_logic_greaterThan_value_name.get(org.apache.struts.taglib.logic.GreaterThanTag.class);
      _jspx_th_logic_greaterThan_0.setPageContext(_jspx_page_context);
      _jspx_th_logic_greaterThan_0.setParent(null);
      _jspx_th_logic_greaterThan_0.setName("hasSomethingToDisplay");
      _jspx_th_logic_greaterThan_0.setValue("0");
      int _jspx_eval_logic_greaterThan_0 = _jspx_th_logic_greaterThan_0.doStartTag();
      if (_jspx_eval_logic_greaterThan_0 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
        do {
          out.write('\r');
          out.write('\n');
          out.write('	');
          //  logic:notEmpty
          org.apache.struts.taglib.logic.NotEmptyTag _jspx_th_logic_notEmpty_0 = (org.apache.struts.taglib.logic.NotEmptyTag) _jspx_tagPool_logic_notEmpty_property_name.get(org.apache.struts.taglib.logic.NotEmptyTag.class);
          _jspx_th_logic_notEmpty_0.setPageContext(_jspx_page_context);
          _jspx_th_logic_notEmpty_0.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_greaterThan_0);
          _jspx_th_logic_notEmpty_0.setName("mySrvDialogForm");
          _jspx_th_logic_notEmpty_0.setProperty("refusedInfo");
          int _jspx_eval_logic_notEmpty_0 = _jspx_th_logic_notEmpty_0.doStartTag();
          if (_jspx_eval_logic_notEmpty_0 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
            do {
              out.write("\r\n\t\t");
              //  bean:define
              org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_6 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
              _jspx_th_bean_define_6.setPageContext(_jspx_page_context);
              _jspx_th_bean_define_6.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_notEmpty_0);
              _jspx_th_bean_define_6.setName("mySrvDialogForm");
              _jspx_th_bean_define_6.setProperty("refusedInfo");
              _jspx_th_bean_define_6.setId("rInfo");
              int _jspx_eval_bean_define_6 = _jspx_th_bean_define_6.doStartTag();
              if (_jspx_th_bean_define_6.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_6);
                return;
              }
              _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_6);
              java.lang.Object rInfo = null;
              rInfo = (java.lang.Object) _jspx_page_context.findAttribute("rInfo");
              out.write('\n');
              out.write('	');
              out.write('	');
              //  bean:define
              org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_7 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
              _jspx_th_bean_define_7.setPageContext(_jspx_page_context);
              _jspx_th_bean_define_7.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_notEmpty_0);
              _jspx_th_bean_define_7.setName("rInfo");
              _jspx_th_bean_define_7.setProperty("friend_name");
              _jspx_th_bean_define_7.setId("rName");
              int _jspx_eval_bean_define_7 = _jspx_th_bean_define_7.doStartTag();
              if (_jspx_th_bean_define_7.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_7);
                return;
              }
              _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_7);
              java.lang.Object rName = null;
              rName = (java.lang.Object) _jspx_page_context.findAttribute("rName");
              out.write('\n');
              out.write('	');
              out.write('	');
              //  bean:define
              org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_8 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
              _jspx_th_bean_define_8.setPageContext(_jspx_page_context);
              _jspx_th_bean_define_8.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_notEmpty_0);
              _jspx_th_bean_define_8.setName("rInfo");
              _jspx_th_bean_define_8.setProperty("notification");
              _jspx_th_bean_define_8.setId("notification");
              int _jspx_eval_bean_define_8 = _jspx_th_bean_define_8.doStartTag();
              if (_jspx_th_bean_define_8.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_8);
                return;
              }
              _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_8);
              java.lang.Object notification = null;
              notification = (java.lang.Object) _jspx_page_context.findAttribute("notification");
              out.write('\n');
              out.write('	');
              out.write('	');
              //  bean:define
              org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_9 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
              _jspx_th_bean_define_9.setPageContext(_jspx_page_context);
              _jspx_th_bean_define_9.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_notEmpty_0);
              _jspx_th_bean_define_9.setName("notification");
              _jspx_th_bean_define_9.setProperty("id");
              _jspx_th_bean_define_9.setId("nId");
              int _jspx_eval_bean_define_9 = _jspx_th_bean_define_9.doStartTag();
              if (_jspx_th_bean_define_9.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_9);
                return;
              }
              _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_9);
              java.lang.Object nId = null;
              nId = (java.lang.Object) _jspx_page_context.findAttribute("nId");
              out.write("\r\n\t\t<br/><span class=\"bigWord\">");
              out.print(rName);
              out.write("</span> ");
              out.print(DicoTools.dico(dico_lang , "srv_communion/refused_your_demand"));
              out.write("\r\n\t\t<hr class=\"spacer\" />\r\n\t\t<input type=\"button\" class=\"genericBt\" value=\"");
              out.print(DicoTools.dico(dico_lang , "srv_communion/refused_your_demand_button"));
              out.write("\" onclick=\"simpleAjaxRequest('srvDialogConfig.do?applicationId=");
              out.print(Application.NativeApplication.EARS_COMMUNION.getApplication().getId());
              out.write("&dispatch=delete&notificationId=");
              out.print(nId);
              out.write("', function(){ endSrvDialog('accept') } )\" />\t\t\r\n\t\t<!-- <input type=\"button\" class=\"genericBt\" value=\"");
              out.print(DicoTools.dico(dico_lang , "srv_communion/refused_your_demand_button"));
              out.write("\" onclick=\"endSrvDialog('refused')\" /> -->\t\t\r\n\t");
              int evalDoAfterBody = _jspx_th_logic_notEmpty_0.doAfterBody();
              if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                break;
            } while (true);
          }
          if (_jspx_th_logic_notEmpty_0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
            _jspx_tagPool_logic_notEmpty_property_name.reuse(_jspx_th_logic_notEmpty_0);
            return;
          }
          _jspx_tagPool_logic_notEmpty_property_name.reuse(_jspx_th_logic_notEmpty_0);
          out.write("\n\t\n\t");
          //  logic:notEmpty
          org.apache.struts.taglib.logic.NotEmptyTag _jspx_th_logic_notEmpty_1 = (org.apache.struts.taglib.logic.NotEmptyTag) _jspx_tagPool_logic_notEmpty_property_name.get(org.apache.struts.taglib.logic.NotEmptyTag.class);
          _jspx_th_logic_notEmpty_1.setPageContext(_jspx_page_context);
          _jspx_th_logic_notEmpty_1.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_greaterThan_0);
          _jspx_th_logic_notEmpty_1.setName("mySrvDialogForm");
          _jspx_th_logic_notEmpty_1.setProperty("acceptedInfo");
          int _jspx_eval_logic_notEmpty_1 = _jspx_th_logic_notEmpty_1.doStartTag();
          if (_jspx_eval_logic_notEmpty_1 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
            do {
              out.write('\n');
              out.write('	');
              out.write('	');
              //  bean:define
              org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_10 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
              _jspx_th_bean_define_10.setPageContext(_jspx_page_context);
              _jspx_th_bean_define_10.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_notEmpty_1);
              _jspx_th_bean_define_10.setName("mySrvDialogForm");
              _jspx_th_bean_define_10.setProperty("acceptedInfo");
              _jspx_th_bean_define_10.setId("rInfo");
              int _jspx_eval_bean_define_10 = _jspx_th_bean_define_10.doStartTag();
              if (_jspx_th_bean_define_10.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_10);
                return;
              }
              _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_10);
              java.lang.Object rInfo = null;
              rInfo = (java.lang.Object) _jspx_page_context.findAttribute("rInfo");
              out.write('\n');
              out.write('	');
              out.write('	');
              //  bean:define
              org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_11 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
              _jspx_th_bean_define_11.setPageContext(_jspx_page_context);
              _jspx_th_bean_define_11.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_notEmpty_1);
              _jspx_th_bean_define_11.setName("rInfo");
              _jspx_th_bean_define_11.setProperty("friend_name");
              _jspx_th_bean_define_11.setId("rName");
              int _jspx_eval_bean_define_11 = _jspx_th_bean_define_11.doStartTag();
              if (_jspx_th_bean_define_11.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_11);
                return;
              }
              _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_11);
              java.lang.Object rName = null;
              rName = (java.lang.Object) _jspx_page_context.findAttribute("rName");
              out.write('\n');
              out.write('	');
              out.write('	');
              //  bean:define
              org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_12 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
              _jspx_th_bean_define_12.setPageContext(_jspx_page_context);
              _jspx_th_bean_define_12.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_notEmpty_1);
              _jspx_th_bean_define_12.setName("rInfo");
              _jspx_th_bean_define_12.setProperty("notification");
              _jspx_th_bean_define_12.setId("notification");
              int _jspx_eval_bean_define_12 = _jspx_th_bean_define_12.doStartTag();
              if (_jspx_th_bean_define_12.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_12);
                return;
              }
              _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_12);
              java.lang.Object notification = null;
              notification = (java.lang.Object) _jspx_page_context.findAttribute("notification");
              out.write('\n');
              out.write('	');
              out.write('	');
              //  bean:define
              org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_13 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
              _jspx_th_bean_define_13.setPageContext(_jspx_page_context);
              _jspx_th_bean_define_13.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_notEmpty_1);
              _jspx_th_bean_define_13.setName("notification");
              _jspx_th_bean_define_13.setProperty("id");
              _jspx_th_bean_define_13.setId("nId");
              int _jspx_eval_bean_define_13 = _jspx_th_bean_define_13.doStartTag();
              if (_jspx_th_bean_define_13.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_13);
                return;
              }
              _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_13);
              java.lang.Object nId = null;
              nId = (java.lang.Object) _jspx_page_context.findAttribute("nId");
              out.write("\n\t\t<br/><span class=\"bigWord\">");
              out.print(rName);
              out.write("</span> ");
              out.print(DicoTools.dico(dico_lang , "srv_communion/message_accept"));
              out.write("\n\t\t<hr class=\"spacer\" />\n\t\t<input type=\"button\" class=\"genericBt\" value=\"OK\" onclick=\"simpleAjaxRequest('srvDialogConfig.do?applicationId=");
              out.print(Application.NativeApplication.EARS_COMMUNION.getApplication().getId());
              out.write("&dispatch=delete&notificationId=");
              out.print(nId);
              out.write("', function(){ endSrvDialog('accept') } )\" />\t\t\n\t");
              int evalDoAfterBody = _jspx_th_logic_notEmpty_1.doAfterBody();
              if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                break;
            } while (true);
          }
          if (_jspx_th_logic_notEmpty_1.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
            _jspx_tagPool_logic_notEmpty_property_name.reuse(_jspx_th_logic_notEmpty_1);
            return;
          }
          _jspx_tagPool_logic_notEmpty_property_name.reuse(_jspx_th_logic_notEmpty_1);
          out.write("\r\n\r\n\t");
          //  logic:notEmpty
          org.apache.struts.taglib.logic.NotEmptyTag _jspx_th_logic_notEmpty_2 = (org.apache.struts.taglib.logic.NotEmptyTag) _jspx_tagPool_logic_notEmpty_property_name.get(org.apache.struts.taglib.logic.NotEmptyTag.class);
          _jspx_th_logic_notEmpty_2.setPageContext(_jspx_page_context);
          _jspx_th_logic_notEmpty_2.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_greaterThan_0);
          _jspx_th_logic_notEmpty_2.setName("mySrvDialogForm");
          _jspx_th_logic_notEmpty_2.setProperty("separatedInfo");
          int _jspx_eval_logic_notEmpty_2 = _jspx_th_logic_notEmpty_2.doStartTag();
          if (_jspx_eval_logic_notEmpty_2 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
            do {
              out.write("\r\n\t\t");
              //  bean:define
              org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_14 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
              _jspx_th_bean_define_14.setPageContext(_jspx_page_context);
              _jspx_th_bean_define_14.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_notEmpty_2);
              _jspx_th_bean_define_14.setName("mySrvDialogForm");
              _jspx_th_bean_define_14.setProperty("separatedInfo");
              _jspx_th_bean_define_14.setId("sInfo");
              int _jspx_eval_bean_define_14 = _jspx_th_bean_define_14.doStartTag();
              if (_jspx_th_bean_define_14.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_14);
                return;
              }
              _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_14);
              java.lang.Object sInfo = null;
              sInfo = (java.lang.Object) _jspx_page_context.findAttribute("sInfo");
              out.write('\n');
              out.write('	');
              out.write('	');
              //  bean:define
              org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_15 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
              _jspx_th_bean_define_15.setPageContext(_jspx_page_context);
              _jspx_th_bean_define_15.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_notEmpty_2);
              _jspx_th_bean_define_15.setName("sInfo");
              _jspx_th_bean_define_15.setProperty("friend");
              _jspx_th_bean_define_15.setId("friend");
              int _jspx_eval_bean_define_15 = _jspx_th_bean_define_15.doStartTag();
              if (_jspx_th_bean_define_15.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_15);
                return;
              }
              _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_15);
              java.lang.Object friend = null;
              friend = (java.lang.Object) _jspx_page_context.findAttribute("friend");
              out.write("\r\n\t\t");
              //  bean:define
              org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_16 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
              _jspx_th_bean_define_16.setPageContext(_jspx_page_context);
              _jspx_th_bean_define_16.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_notEmpty_2);
              _jspx_th_bean_define_16.setName("friend");
              _jspx_th_bean_define_16.setProperty("object_login");
              _jspx_th_bean_define_16.setId("sName");
              int _jspx_eval_bean_define_16 = _jspx_th_bean_define_16.doStartTag();
              if (_jspx_th_bean_define_16.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_16);
                return;
              }
              _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_16);
              java.lang.Object sName = null;
              sName = (java.lang.Object) _jspx_page_context.findAttribute("sName");
              out.write('\n');
              out.write('	');
              out.write('	');
              //  bean:define
              org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_17 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
              _jspx_th_bean_define_17.setPageContext(_jspx_page_context);
              _jspx_th_bean_define_17.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_notEmpty_2);
              _jspx_th_bean_define_17.setName("friend");
              _jspx_th_bean_define_17.setProperty("id");
              _jspx_th_bean_define_17.setId("sId");
              int _jspx_eval_bean_define_17 = _jspx_th_bean_define_17.doStartTag();
              if (_jspx_th_bean_define_17.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_17);
                return;
              }
              _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_17);
              java.lang.Object sId = null;
              sId = (java.lang.Object) _jspx_page_context.findAttribute("sId");
              out.write('\n');
              out.write('	');
              out.write('	');
              //  bean:define
              org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_18 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
              _jspx_th_bean_define_18.setPageContext(_jspx_page_context);
              _jspx_th_bean_define_18.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_notEmpty_2);
              _jspx_th_bean_define_18.setName("sInfo");
              _jspx_th_bean_define_18.setProperty("notification");
              _jspx_th_bean_define_18.setId("notification");
              int _jspx_eval_bean_define_18 = _jspx_th_bean_define_18.doStartTag();
              if (_jspx_th_bean_define_18.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_18);
                return;
              }
              _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_18);
              java.lang.Object notification = null;
              notification = (java.lang.Object) _jspx_page_context.findAttribute("notification");
              out.write('\n');
              out.write('	');
              out.write('	');
              //  bean:define
              org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_19 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
              _jspx_th_bean_define_19.setPageContext(_jspx_page_context);
              _jspx_th_bean_define_19.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_notEmpty_2);
              _jspx_th_bean_define_19.setName("notification");
              _jspx_th_bean_define_19.setProperty("id");
              _jspx_th_bean_define_19.setId("nId");
              int _jspx_eval_bean_define_19 = _jspx_th_bean_define_19.doStartTag();
              if (_jspx_th_bean_define_19.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_19);
                return;
              }
              _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_19);
              java.lang.Object nId = null;
              nId = (java.lang.Object) _jspx_page_context.findAttribute("nId");
              out.write("\r\n\t\t<span class=\"bigWord\">");
              out.print(sName);
              out.write("</span>");
              out.print(DicoTools.dico(dico_lang , "srv_communion/divorced_from_you"));
              out.write("\r\n\r\n\t\t<hr class=\"spacer\" />\r\n\t\t<input type=\"button\" class=\"genericBt\" value=\"");
              out.print(DicoTools.dico(dico_lang , "srv_communion/divorced_from_you_button"));
              out.write("\" onclick= \"simpleAjaxRequest('srvDialogConfig.do?applicationId=");
              out.print(Application.NativeApplication.EARS_COMMUNION.getApplication().getId());
              out.write("&dispatch=delete&notificationId=");
              out.print(nId);
              out.write("', function(){ endSrvDialog('accept') } )\" />\r\n\t");
              int evalDoAfterBody = _jspx_th_logic_notEmpty_2.doAfterBody();
              if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                break;
            } while (true);
          }
          if (_jspx_th_logic_notEmpty_2.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
            _jspx_tagPool_logic_notEmpty_property_name.reuse(_jspx_th_logic_notEmpty_2);
            return;
          }
          _jspx_tagPool_logic_notEmpty_property_name.reuse(_jspx_th_logic_notEmpty_2);
          out.write("\r\n\t\r\n\t");
          //  logic:notEmpty
          org.apache.struts.taglib.logic.NotEmptyTag _jspx_th_logic_notEmpty_3 = (org.apache.struts.taglib.logic.NotEmptyTag) _jspx_tagPool_logic_notEmpty_property_name.get(org.apache.struts.taglib.logic.NotEmptyTag.class);
          _jspx_th_logic_notEmpty_3.setPageContext(_jspx_page_context);
          _jspx_th_logic_notEmpty_3.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_greaterThan_0);
          _jspx_th_logic_notEmpty_3.setName("mySrvDialogForm");
          _jspx_th_logic_notEmpty_3.setProperty("cancelList");
          int _jspx_eval_logic_notEmpty_3 = _jspx_th_logic_notEmpty_3.doStartTag();
          if (_jspx_eval_logic_notEmpty_3 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
            do {
              out.write("\r\n\t\t");
              //  logic:iterate
              org.apache.struts.taglib.logic.IterateTag _jspx_th_logic_iterate_0 = (org.apache.struts.taglib.logic.IterateTag) _jspx_tagPool_logic_iterate_property_name_id.get(org.apache.struts.taglib.logic.IterateTag.class);
              _jspx_th_logic_iterate_0.setPageContext(_jspx_page_context);
              _jspx_th_logic_iterate_0.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_notEmpty_3);
              _jspx_th_logic_iterate_0.setName("mySrvDialogForm");
              _jspx_th_logic_iterate_0.setProperty("cancelList");
              _jspx_th_logic_iterate_0.setId("srvDialogData");
              int _jspx_eval_logic_iterate_0 = _jspx_th_logic_iterate_0.doStartTag();
              if (_jspx_eval_logic_iterate_0 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
                java.lang.Object srvDialogData = null;
                if (_jspx_eval_logic_iterate_0 != javax.servlet.jsp.tagext.Tag.EVAL_BODY_INCLUDE) {
                  out = _jspx_page_context.pushBody();
                  _jspx_th_logic_iterate_0.setBodyContent((javax.servlet.jsp.tagext.BodyContent) out);
                  _jspx_th_logic_iterate_0.doInitBody();
                }
                srvDialogData = (java.lang.Object) _jspx_page_context.findAttribute("srvDialogData");
                do {
                  out.write("\n\t\t\t");
                  //  bean:define
                  org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_20 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
                  _jspx_th_bean_define_20.setPageContext(_jspx_page_context);
                  _jspx_th_bean_define_20.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_iterate_0);
                  _jspx_th_bean_define_20.setName("srvDialogData");
                  _jspx_th_bean_define_20.setProperty("friend");
                  _jspx_th_bean_define_20.setId("vObjectData");
                  int _jspx_eval_bean_define_20 = _jspx_th_bean_define_20.doStartTag();
                  if (_jspx_th_bean_define_20.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                    _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_20);
                    return;
                  }
                  _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_20);
                  java.lang.Object vObjectData = null;
                  vObjectData = (java.lang.Object) _jspx_page_context.findAttribute("vObjectData");
                  out.write("\r\n\t\t\t");
                  //  bean:define
                  org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_21 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
                  _jspx_th_bean_define_21.setPageContext(_jspx_page_context);
                  _jspx_th_bean_define_21.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_iterate_0);
                  _jspx_th_bean_define_21.setName("vObjectData");
                  _jspx_th_bean_define_21.setProperty("id");
                  _jspx_th_bean_define_21.setId("cId");
                  int _jspx_eval_bean_define_21 = _jspx_th_bean_define_21.doStartTag();
                  if (_jspx_th_bean_define_21.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                    _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_21);
                    return;
                  }
                  _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_21);
                  java.lang.Object cId = null;
                  cId = (java.lang.Object) _jspx_page_context.findAttribute("cId");
                  out.write("\r\n\t\t\t");
                  //  bean:define
                  org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_22 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
                  _jspx_th_bean_define_22.setPageContext(_jspx_page_context);
                  _jspx_th_bean_define_22.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_iterate_0);
                  _jspx_th_bean_define_22.setName("vObjectData");
                  _jspx_th_bean_define_22.setProperty("object_login");
                  _jspx_th_bean_define_22.setId("cName");
                  int _jspx_eval_bean_define_22 = _jspx_th_bean_define_22.doStartTag();
                  if (_jspx_th_bean_define_22.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                    _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_22);
                    return;
                  }
                  _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_22);
                  java.lang.Object cName = null;
                  cName = (java.lang.Object) _jspx_page_context.findAttribute("cName");
                  out.write("\n\t\t\t");
                  //  bean:define
                  org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_23 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
                  _jspx_th_bean_define_23.setPageContext(_jspx_page_context);
                  _jspx_th_bean_define_23.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_iterate_0);
                  _jspx_th_bean_define_23.setName("srvDialogData");
                  _jspx_th_bean_define_23.setProperty("notification");
                  _jspx_th_bean_define_23.setId("notification");
                  int _jspx_eval_bean_define_23 = _jspx_th_bean_define_23.doStartTag();
                  if (_jspx_th_bean_define_23.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                    _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_23);
                    return;
                  }
                  _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_23);
                  java.lang.Object notification = null;
                  notification = (java.lang.Object) _jspx_page_context.findAttribute("notification");
                  out.write("\n\t\t\t");
                  //  bean:define
                  org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_24 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
                  _jspx_th_bean_define_24.setPageContext(_jspx_page_context);
                  _jspx_th_bean_define_24.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_iterate_0);
                  _jspx_th_bean_define_24.setName("notification");
                  _jspx_th_bean_define_24.setProperty("id");
                  _jspx_th_bean_define_24.setId("nId");
                  int _jspx_eval_bean_define_24 = _jspx_th_bean_define_24.doStartTag();
                  if (_jspx_th_bean_define_24.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                    _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_24);
                    return;
                  }
                  _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_24);
                  java.lang.Object nId = null;
                  nId = (java.lang.Object) _jspx_page_context.findAttribute("nId");
                  out.write("\r\n\t\t\t<span class=\"bigWord\">");
                  out.print(cName);
                  out.write("</span> ");
                  out.print(DicoTools.dico(dico_lang , "srv_communion/cancelled_his_demand"));
                  out.write("\r\n\t\t\t<hr class=\"spacer\" />\r\n\t\t\t<input type=\"button\" class=\"genericBt\" value=\"");
                  out.print(DicoTools.dico(dico_lang , "srv_communion/cancelled_his_demand_button"));
                  out.write("\" onclick= \"simpleAjaxRequest('srvDialogConfig.do?applicationId=");
                  out.print(Application.NativeApplication.EARS_COMMUNION.getApplication().getId());
                  out.write("&dispatch=delete&notificationId=");
                  out.print(nId);
                  out.write("', function(){ endSrvDialog('accept') } )\" />\r\n\t\t\t\r\n\t\t");
                  int evalDoAfterBody = _jspx_th_logic_iterate_0.doAfterBody();
                  srvDialogData = (java.lang.Object) _jspx_page_context.findAttribute("srvDialogData");
                  if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                    break;
                } while (true);
                if (_jspx_eval_logic_iterate_0 != javax.servlet.jsp.tagext.Tag.EVAL_BODY_INCLUDE) {
                  out = _jspx_page_context.popBody();
                }
              }
              if (_jspx_th_logic_iterate_0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                _jspx_tagPool_logic_iterate_property_name_id.reuse(_jspx_th_logic_iterate_0);
                return;
              }
              _jspx_tagPool_logic_iterate_property_name_id.reuse(_jspx_th_logic_iterate_0);
              out.write('\r');
              out.write('\n');
              out.write('	');
              int evalDoAfterBody = _jspx_th_logic_notEmpty_3.doAfterBody();
              if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                break;
            } while (true);
          }
          if (_jspx_th_logic_notEmpty_3.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
            _jspx_tagPool_logic_notEmpty_property_name.reuse(_jspx_th_logic_notEmpty_3);
            return;
          }
          _jspx_tagPool_logic_notEmpty_property_name.reuse(_jspx_th_logic_notEmpty_3);
          out.write("\r\n\t\r\n\t");
          //  logic:notEmpty
          org.apache.struts.taglib.logic.NotEmptyTag _jspx_th_logic_notEmpty_4 = (org.apache.struts.taglib.logic.NotEmptyTag) _jspx_tagPool_logic_notEmpty_property_name.get(org.apache.struts.taglib.logic.NotEmptyTag.class);
          _jspx_th_logic_notEmpty_4.setPageContext(_jspx_page_context);
          _jspx_th_logic_notEmpty_4.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_greaterThan_0);
          _jspx_th_logic_notEmpty_4.setName("mySrvDialogForm");
          _jspx_th_logic_notEmpty_4.setProperty("waitingList");
          int _jspx_eval_logic_notEmpty_4 = _jspx_th_logic_notEmpty_4.doStartTag();
          if (_jspx_eval_logic_notEmpty_4 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
            do {
              out.write("\r\n\t\t<hr class=\"spacer\" />\t\r\n\t\t");
              //  logic:iterate
              org.apache.struts.taglib.logic.IterateTag _jspx_th_logic_iterate_1 = (org.apache.struts.taglib.logic.IterateTag) _jspx_tagPool_logic_iterate_property_name_id.get(org.apache.struts.taglib.logic.IterateTag.class);
              _jspx_th_logic_iterate_1.setPageContext(_jspx_page_context);
              _jspx_th_logic_iterate_1.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_notEmpty_4);
              _jspx_th_logic_iterate_1.setName("mySrvDialogForm");
              _jspx_th_logic_iterate_1.setProperty("waitingList");
              _jspx_th_logic_iterate_1.setId("srvDialogData");
              int _jspx_eval_logic_iterate_1 = _jspx_th_logic_iterate_1.doStartTag();
              if (_jspx_eval_logic_iterate_1 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
                java.lang.Object srvDialogData = null;
                if (_jspx_eval_logic_iterate_1 != javax.servlet.jsp.tagext.Tag.EVAL_BODY_INCLUDE) {
                  out = _jspx_page_context.pushBody();
                  _jspx_th_logic_iterate_1.setBodyContent((javax.servlet.jsp.tagext.BodyContent) out);
                  _jspx_th_logic_iterate_1.doInitBody();
                }
                srvDialogData = (java.lang.Object) _jspx_page_context.findAttribute("srvDialogData");
                do {
                  out.write("\n\t\t\t");
                  //  bean:define
                  org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_25 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
                  _jspx_th_bean_define_25.setPageContext(_jspx_page_context);
                  _jspx_th_bean_define_25.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_iterate_1);
                  _jspx_th_bean_define_25.setName("srvDialogData");
                  _jspx_th_bean_define_25.setProperty("object");
                  _jspx_th_bean_define_25.setId("vObjectData");
                  int _jspx_eval_bean_define_25 = _jspx_th_bean_define_25.doStartTag();
                  if (_jspx_th_bean_define_25.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                    _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_25);
                    return;
                  }
                  _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_25);
                  java.lang.Object vObjectData = null;
                  vObjectData = (java.lang.Object) _jspx_page_context.findAttribute("vObjectData");
                  out.write("\n\t\t\t");
                  //  bean:define
                  org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_26 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
                  _jspx_th_bean_define_26.setPageContext(_jspx_page_context);
                  _jspx_th_bean_define_26.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_iterate_1);
                  _jspx_th_bean_define_26.setName("vObjectData");
                  _jspx_th_bean_define_26.setProperty("id");
                  _jspx_th_bean_define_26.setId("wId");
                  int _jspx_eval_bean_define_26 = _jspx_th_bean_define_26.doStartTag();
                  if (_jspx_th_bean_define_26.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                    _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_26);
                    return;
                  }
                  _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_26);
                  java.lang.Object wId = null;
                  wId = (java.lang.Object) _jspx_page_context.findAttribute("wId");
                  out.write("\r\n\t\t\t");
                  //  bean:define
                  org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_27 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
                  _jspx_th_bean_define_27.setPageContext(_jspx_page_context);
                  _jspx_th_bean_define_27.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_iterate_1);
                  _jspx_th_bean_define_27.setName("vObjectData");
                  _jspx_th_bean_define_27.setProperty("object_login");
                  _jspx_th_bean_define_27.setId("wName");
                  int _jspx_eval_bean_define_27 = _jspx_th_bean_define_27.doStartTag();
                  if (_jspx_th_bean_define_27.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                    _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_27);
                    return;
                  }
                  _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_27);
                  java.lang.Object wName = null;
                  wName = (java.lang.Object) _jspx_page_context.findAttribute("wName");
                  out.write("\r\n\t\t\t<input type=\"button\" class=\"genericBt\" value=\"");
                  out.print(DicoTools.dico(dico_lang , "srv_communion/button_accept"));
                  out.write("\" onclick=\"startSrvDialogAction('srvDialogConfig.do?applicationId=");
                  out.print(Application.NativeApplication.EARS_COMMUNION.getApplication().getId());
                  out.write("&dispatch=accept&friendId=");
                  out.print(wId);
                  out.write("&friendName=");
                  out.print(wName);
                  out.write("', function(){ endSrvDialog('accept') } )\" />\r\n\t\t\t<span class=\"bigWord\">");
                  out.print(wName);
                  out.write("</span> ");
                  out.print(DicoTools.dico(dico_lang , "srv_communion/proposes_to_you"));
                  out.write("\r\n\t\t\t<hr class=\"spacer\" />\t\r\n\t\t");
                  int evalDoAfterBody = _jspx_th_logic_iterate_1.doAfterBody();
                  srvDialogData = (java.lang.Object) _jspx_page_context.findAttribute("srvDialogData");
                  if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                    break;
                } while (true);
                if (_jspx_eval_logic_iterate_1 != javax.servlet.jsp.tagext.Tag.EVAL_BODY_INCLUDE) {
                  out = _jspx_page_context.popBody();
                }
              }
              if (_jspx_th_logic_iterate_1.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                _jspx_tagPool_logic_iterate_property_name_id.reuse(_jspx_th_logic_iterate_1);
                return;
              }
              _jspx_tagPool_logic_iterate_property_name_id.reuse(_jspx_th_logic_iterate_1);
              out.write("\r\n\t\t<div align=\"center\"><input type=\"button\" class=\"genericDeleteBt\" value=\"");
              out.print(DicoTools.dico(dico_lang , "srv_communion/button_refuse_all"));
              out.write("\" onclick= \"simpleAjaxRequest('srvDialogConfig.do?applicationId=");
              out.print(Application.NativeApplication.EARS_COMMUNION.getApplication().getId());
              out.write("&dispatch=denyAll', function(){ endSrvDialog('accept') } )\" /></div>\r\n\t");
              int evalDoAfterBody = _jspx_th_logic_notEmpty_4.doAfterBody();
              if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                break;
            } while (true);
          }
          if (_jspx_th_logic_notEmpty_4.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
            _jspx_tagPool_logic_notEmpty_property_name.reuse(_jspx_th_logic_notEmpty_4);
            return;
          }
          _jspx_tagPool_logic_notEmpty_property_name.reuse(_jspx_th_logic_notEmpty_4);
          out.write("\r\n\t\r\n");
          int evalDoAfterBody = _jspx_th_logic_greaterThan_0.doAfterBody();
          if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
            break;
        } while (true);
      }
      if (_jspx_th_logic_greaterThan_0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
        _jspx_tagPool_logic_greaterThan_value_name.reuse(_jspx_th_logic_greaterThan_0);
        return;
      }
      _jspx_tagPool_logic_greaterThan_value_name.reuse(_jspx_th_logic_greaterThan_0);
      out.write("\r\n\t\t\r\n");
      //  logic:lessEqual
      org.apache.struts.taglib.logic.LessEqualTag _jspx_th_logic_lessEqual_0 = (org.apache.struts.taglib.logic.LessEqualTag) _jspx_tagPool_logic_lessEqual_value_name.get(org.apache.struts.taglib.logic.LessEqualTag.class);
      _jspx_th_logic_lessEqual_0.setPageContext(_jspx_page_context);
      _jspx_th_logic_lessEqual_0.setParent(null);
      _jspx_th_logic_lessEqual_0.setName("hasSomethingToDisplay");
      _jspx_th_logic_lessEqual_0.setValue("0");
      int _jspx_eval_logic_lessEqual_0 = _jspx_th_logic_lessEqual_0.doStartTag();
      if (_jspx_eval_logic_lessEqual_0 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
        do {
          out.write("\r\n\t<div class=\"main-cadre-contener\">\r\n\t\t<div class=\"main-cadre-top\"><h2>");
          out.print(DicoTools.dico(dico_lang , "services/configure"));
          out.write("</h2></div>\r\n\t\t<div class=\"main-cadre-content\">\r\n\t\t\t<hr class=\"spacer\"/>\r\n\t\t\t<!-- ******************************************** CONTENT ***************************************************** --> \r\n\t\t\t\r\n\t\t\t<!-- Affichage de la page de gestion du service -->\r\n\t\t\t");
          //  logic:equal
          org.apache.struts.taglib.logic.EqualTag _jspx_th_logic_equal_0 = (org.apache.struts.taglib.logic.EqualTag) _jspx_tagPool_logic_equal_value_name.get(org.apache.struts.taglib.logic.EqualTag.class);
          _jspx_th_logic_equal_0.setPageContext(_jspx_page_context);
          _jspx_th_logic_equal_0.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_lessEqual_0);
          _jspx_th_logic_equal_0.setName("hasSomethingToDisplay");
          _jspx_th_logic_equal_0.setValue("0");
          int _jspx_eval_logic_equal_0 = _jspx_th_logic_equal_0.doStartTag();
          if (_jspx_eval_logic_equal_0 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
            do {
              out.write("\r\n\t\t\t\r\n\t\t\t\t<script type=\"text/javascript\">\r\n\t\t\t\t\tgSrvErrorFlag = true;\t// on force le flag a true, pour ???viter les messages\r\n\t\t\t\t</script>\t\t\r\n\t\t\t\t");
              //  html:form
              org.apache.struts.taglib.html.FormTag _jspx_th_html_form_0 = (org.apache.struts.taglib.html.FormTag) _jspx_tagPool_html_form_styleId_styleClass_action.get(org.apache.struts.taglib.html.FormTag.class);
              _jspx_th_html_form_0.setPageContext(_jspx_page_context);
              _jspx_th_html_form_0.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_equal_0);
              _jspx_th_html_form_0.setAction("action/srvDialogConfig");
              _jspx_th_html_form_0.setStyleId("srvDialogConfig");
              _jspx_th_html_form_0.setStyleClass("srvConfigForm");
              int _jspx_eval_html_form_0 = _jspx_th_html_form_0.doStartTag();
              if (_jspx_eval_html_form_0 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
                do {
                  out.write("\n\t\t\t\t\t");
                  //  bean:define
                  org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_28 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
                  _jspx_th_bean_define_28.setPageContext(_jspx_page_context);
                  _jspx_th_bean_define_28.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_form_0);
                  _jspx_th_bean_define_28.setId("subscriptionId");
                  _jspx_th_bean_define_28.setName("mySrvDialogForm");
                  _jspx_th_bean_define_28.setProperty("subscriptionId");
                  int _jspx_eval_bean_define_28 = _jspx_th_bean_define_28.doStartTag();
                  if (_jspx_th_bean_define_28.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                    _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_28);
                    return;
                  }
                  _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_28);
                  java.lang.Object subscriptionId = null;
                  subscriptionId = (java.lang.Object) _jspx_page_context.findAttribute("subscriptionId");
                  out.write("\n\t\t\t\t\t");
                  //  html:hidden
                  org.apache.struts.taglib.html.HiddenTag _jspx_th_html_hidden_0 = (org.apache.struts.taglib.html.HiddenTag) _jspx_tagPool_html_hidden_value_property_nobody.get(org.apache.struts.taglib.html.HiddenTag.class);
                  _jspx_th_html_hidden_0.setPageContext(_jspx_page_context);
                  _jspx_th_html_hidden_0.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_form_0);
                  _jspx_th_html_hidden_0.setProperty("subscriptionId");
                  _jspx_th_html_hidden_0.setValue(subscriptionId.toString() );
                  int _jspx_eval_html_hidden_0 = _jspx_th_html_hidden_0.doStartTag();
                  if (_jspx_th_html_hidden_0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                    _jspx_tagPool_html_hidden_value_property_nobody.reuse(_jspx_th_html_hidden_0);
                    return;
                  }
                  _jspx_tagPool_html_hidden_value_property_nobody.reuse(_jspx_th_html_hidden_0);
                  out.write("\r\n\t\t\t\t\t");
                  if (_jspx_meth_html_hidden_1(_jspx_th_html_form_0, _jspx_page_context))
                    return;
                  out.write("\r\n\t\t\t\t\t");
                  if (_jspx_meth_logic_equal_1(_jspx_th_html_form_0, _jspx_page_context))
                    return;
                  out.write("\r\n\t\t\t\t\t\r\n\t\t\t\t\t");
                  if (_jspx_meth_logic_equal_2(_jspx_th_html_form_0, _jspx_page_context))
                    return;
                  out.write("\r\n\t\t\t\t\t\r\n\t\t\t\t\t");
                  //  logic:equal
                  org.apache.struts.taglib.logic.EqualTag _jspx_th_logic_equal_3 = (org.apache.struts.taglib.logic.EqualTag) _jspx_tagPool_logic_equal_value_name.get(org.apache.struts.taglib.logic.EqualTag.class);
                  _jspx_th_logic_equal_3.setPageContext(_jspx_page_context);
                  _jspx_th_logic_equal_3.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_form_0);
                  _jspx_th_logic_equal_3.setName("isMarried");
                  _jspx_th_logic_equal_3.setValue("0");
                  int _jspx_eval_logic_equal_3 = _jspx_th_logic_equal_3.doStartTag();
                  if (_jspx_eval_logic_equal_3 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
                    do {
                      out.write("\r\n\t\t\t\t\t\t");
                      //  logic:equal
                      org.apache.struts.taglib.logic.EqualTag _jspx_th_logic_equal_4 = (org.apache.struts.taglib.logic.EqualTag) _jspx_tagPool_logic_equal_value_name.get(org.apache.struts.taglib.logic.EqualTag.class);
                      _jspx_th_logic_equal_4.setPageContext(_jspx_page_context);
                      _jspx_th_logic_equal_4.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_equal_3);
                      _jspx_th_logic_equal_4.setName("isWaiting");
                      _jspx_th_logic_equal_4.setValue("0");
                      int _jspx_eval_logic_equal_4 = _jspx_th_logic_equal_4.doStartTag();
                      if (_jspx_eval_logic_equal_4 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
                        do {
                          out.write("\r\n\t\t\t\t\t\t\t");
                          out.print(DicoTools.dico(dico_lang , "srv_communion/enter_name"));
                          out.write("\r\n\t\t\t\t\t\t\t");
                          if (_jspx_meth_html_text_0(_jspx_th_logic_equal_4, _jspx_page_context))
                            return;
                          out.write("\r\n\t\t\t\t\t\t\t");
                          //  html:submit
                          org.apache.struts.taglib.html.SubmitTag _jspx_th_html_submit_0 = (org.apache.struts.taglib.html.SubmitTag) _jspx_tagPool_html_submit_value_styleClass_property_onclick.get(org.apache.struts.taglib.html.SubmitTag.class);
                          _jspx_th_html_submit_0.setPageContext(_jspx_page_context);
                          _jspx_th_html_submit_0.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_equal_4);
                          _jspx_th_html_submit_0.setProperty("activate");
                          _jspx_th_html_submit_0.setValue(DicoTools.dico(dico_lang , "srv_communion/button_marry_me"));
                          _jspx_th_html_submit_0.setStyleClass("genericBt");
                          _jspx_th_html_submit_0.setOnclick("goDispatch('add', 'dispatchConfig')");
                          int _jspx_eval_html_submit_0 = _jspx_th_html_submit_0.doStartTag();
                          if (_jspx_eval_html_submit_0 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
                            if (_jspx_eval_html_submit_0 != javax.servlet.jsp.tagext.Tag.EVAL_BODY_INCLUDE) {
                              out = _jspx_page_context.pushBody();
                              _jspx_th_html_submit_0.setBodyContent((javax.servlet.jsp.tagext.BodyContent) out);
                              _jspx_th_html_submit_0.doInitBody();
                            }
                            do {
                              out.print(DicoTools.dico(dico_lang , "srv_communion/button_marry_me"));
                              int evalDoAfterBody = _jspx_th_html_submit_0.doAfterBody();
                              if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                              break;
                            } while (true);
                            if (_jspx_eval_html_submit_0 != javax.servlet.jsp.tagext.Tag.EVAL_BODY_INCLUDE) {
                              out = _jspx_page_context.popBody();
                            }
                          }
                          if (_jspx_th_html_submit_0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                            _jspx_tagPool_html_submit_value_styleClass_property_onclick.reuse(_jspx_th_html_submit_0);
                            return;
                          }
                          _jspx_tagPool_html_submit_value_styleClass_property_onclick.reuse(_jspx_th_html_submit_0);
                          out.write("\t\r\n\t\t\t\t\t\t");
                          int evalDoAfterBody = _jspx_th_logic_equal_4.doAfterBody();
                          if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                            break;
                        } while (true);
                      }
                      if (_jspx_th_logic_equal_4.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                        _jspx_tagPool_logic_equal_value_name.reuse(_jspx_th_logic_equal_4);
                        return;
                      }
                      _jspx_tagPool_logic_equal_value_name.reuse(_jspx_th_logic_equal_4);
                      out.write("\r\n\t\t\t\t\t");
                      int evalDoAfterBody = _jspx_th_logic_equal_3.doAfterBody();
                      if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                        break;
                    } while (true);
                  }
                  if (_jspx_th_logic_equal_3.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                    _jspx_tagPool_logic_equal_value_name.reuse(_jspx_th_logic_equal_3);
                    return;
                  }
                  _jspx_tagPool_logic_equal_value_name.reuse(_jspx_th_logic_equal_3);
                  out.write("\r\n\t\t\t\t\t\r\n\t\t\t\t\t");
                  //  logic:equal
                  org.apache.struts.taglib.logic.EqualTag _jspx_th_logic_equal_5 = (org.apache.struts.taglib.logic.EqualTag) _jspx_tagPool_logic_equal_value_name.get(org.apache.struts.taglib.logic.EqualTag.class);
                  _jspx_th_logic_equal_5.setPageContext(_jspx_page_context);
                  _jspx_th_logic_equal_5.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_form_0);
                  _jspx_th_logic_equal_5.setName("isMarried");
                  _jspx_th_logic_equal_5.setValue("1");
                  int _jspx_eval_logic_equal_5 = _jspx_th_logic_equal_5.doStartTag();
                  if (_jspx_eval_logic_equal_5 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
                    do {
                      out.write("\r\n\t\t\t\t\t\t");
                      //  bean:define
                      org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_29 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
                      _jspx_th_bean_define_29.setPageContext(_jspx_page_context);
                      _jspx_th_bean_define_29.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_equal_5);
                      _jspx_th_bean_define_29.setName("mySrvDialogForm");
                      _jspx_th_bean_define_29.setProperty("friendName");
                      _jspx_th_bean_define_29.setId("friendName");
                      int _jspx_eval_bean_define_29 = _jspx_th_bean_define_29.doStartTag();
                      if (_jspx_th_bean_define_29.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                        _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_29);
                        return;
                      }
                      _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_29);
                      java.lang.Object friendName = null;
                      friendName = (java.lang.Object) _jspx_page_context.findAttribute("friendName");
                      out.write("\r\n\t\t\t\t\t\t");
                      out.print(DicoTools.dico(dico_lang , "srv_communion/youre_married_with"));
                      out.write("<span class=\"bigWord\">");
                      out.print(friendName);
                      out.write("</span>\r\n\t\t\t\t\t\t<hr class=\"spacer\" />\r\n\t\t\t\t\t\t");
                      //  html:submit
                      org.apache.struts.taglib.html.SubmitTag _jspx_th_html_submit_1 = (org.apache.struts.taglib.html.SubmitTag) _jspx_tagPool_html_submit_value_styleClass_property_onclick.get(org.apache.struts.taglib.html.SubmitTag.class);
                      _jspx_th_html_submit_1.setPageContext(_jspx_page_context);
                      _jspx_th_html_submit_1.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_equal_5);
                      _jspx_th_html_submit_1.setProperty("delete");
                      _jspx_th_html_submit_1.setValue(DicoTools.dico(dico_lang , "srv_communion/button_divorce"));
                      _jspx_th_html_submit_1.setStyleClass("genericBt");
                      _jspx_th_html_submit_1.setOnclick("goDispatch('delete', 'dispatchConfig')");
                      int _jspx_eval_html_submit_1 = _jspx_th_html_submit_1.doStartTag();
                      if (_jspx_eval_html_submit_1 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
                        if (_jspx_eval_html_submit_1 != javax.servlet.jsp.tagext.Tag.EVAL_BODY_INCLUDE) {
                          out = _jspx_page_context.pushBody();
                          _jspx_th_html_submit_1.setBodyContent((javax.servlet.jsp.tagext.BodyContent) out);
                          _jspx_th_html_submit_1.doInitBody();
                        }
                        do {
                          out.print(DicoTools.dico(dico_lang , "srv_communion/button_divorce"));
                          int evalDoAfterBody = _jspx_th_html_submit_1.doAfterBody();
                          if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                            break;
                        } while (true);
                        if (_jspx_eval_html_submit_1 != javax.servlet.jsp.tagext.Tag.EVAL_BODY_INCLUDE) {
                          out = _jspx_page_context.popBody();
                        }
                      }
                      if (_jspx_th_html_submit_1.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                        _jspx_tagPool_html_submit_value_styleClass_property_onclick.reuse(_jspx_th_html_submit_1);
                        return;
                      }
                      _jspx_tagPool_html_submit_value_styleClass_property_onclick.reuse(_jspx_th_html_submit_1);
                      out.write("\t\r\n\t\t\t\t\t");
                      int evalDoAfterBody = _jspx_th_logic_equal_5.doAfterBody();
                      if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                        break;
                    } while (true);
                  }
                  if (_jspx_th_logic_equal_5.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                    _jspx_tagPool_logic_equal_value_name.reuse(_jspx_th_logic_equal_5);
                    return;
                  }
                  _jspx_tagPool_logic_equal_value_name.reuse(_jspx_th_logic_equal_5);
                  out.write("\r\n\t\t\t\t\t\r\n\t\t\t\t\t");
                  //  logic:equal
                  org.apache.struts.taglib.logic.EqualTag _jspx_th_logic_equal_6 = (org.apache.struts.taglib.logic.EqualTag) _jspx_tagPool_logic_equal_value_name.get(org.apache.struts.taglib.logic.EqualTag.class);
                  _jspx_th_logic_equal_6.setPageContext(_jspx_page_context);
                  _jspx_th_logic_equal_6.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_form_0);
                  _jspx_th_logic_equal_6.setName("isWaiting");
                  _jspx_th_logic_equal_6.setValue("1");
                  int _jspx_eval_logic_equal_6 = _jspx_th_logic_equal_6.doStartTag();
                  if (_jspx_eval_logic_equal_6 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
                    do {
                      out.write("\r\n\t\t\t\t\t\t");
                      //  bean:define
                      org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_30 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
                      _jspx_th_bean_define_30.setPageContext(_jspx_page_context);
                      _jspx_th_bean_define_30.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_equal_6);
                      _jspx_th_bean_define_30.setName("mySrvDialogForm");
                      _jspx_th_bean_define_30.setProperty("friendName");
                      _jspx_th_bean_define_30.setId("friendName");
                      int _jspx_eval_bean_define_30 = _jspx_th_bean_define_30.doStartTag();
                      if (_jspx_th_bean_define_30.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                        _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_30);
                        return;
                      }
                      _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_30);
                      java.lang.Object friendName = null;
                      friendName = (java.lang.Object) _jspx_page_context.findAttribute("friendName");
                      out.write("\r\n\t\t\t\t\t\t");
                      out.print(DicoTools.dico(dico_lang , "srv_communion/demand_done"));
                      out.write(" <span class=\"bigWord\">");
                      out.print(friendName);
                      out.write("</span>\r\n\t\t\t\t\t\t<hr class=\"spacer\" />\r\n\t\t\t\t\t\t");
                      //  html:submit
                      org.apache.struts.taglib.html.SubmitTag _jspx_th_html_submit_2 = (org.apache.struts.taglib.html.SubmitTag) _jspx_tagPool_html_submit_value_styleClass_property_onclick.get(org.apache.struts.taglib.html.SubmitTag.class);
                      _jspx_th_html_submit_2.setPageContext(_jspx_page_context);
                      _jspx_th_html_submit_2.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_equal_6);
                      _jspx_th_html_submit_2.setProperty("cancel");
                      _jspx_th_html_submit_2.setValue(DicoTools.dico(dico_lang , "srv_communion/button_changed_mind"));
                      _jspx_th_html_submit_2.setStyleClass("genericBt");
                      _jspx_th_html_submit_2.setOnclick("goDispatch('cancel', 'dispatchConfig')");
                      int _jspx_eval_html_submit_2 = _jspx_th_html_submit_2.doStartTag();
                      if (_jspx_eval_html_submit_2 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
                        if (_jspx_eval_html_submit_2 != javax.servlet.jsp.tagext.Tag.EVAL_BODY_INCLUDE) {
                          out = _jspx_page_context.pushBody();
                          _jspx_th_html_submit_2.setBodyContent((javax.servlet.jsp.tagext.BodyContent) out);
                          _jspx_th_html_submit_2.doInitBody();
                        }
                        do {
                          out.print(DicoTools.dico(dico_lang , "srv_communion/button_changed_mind"));
                          int evalDoAfterBody = _jspx_th_html_submit_2.doAfterBody();
                          if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                            break;
                        } while (true);
                        if (_jspx_eval_html_submit_2 != javax.servlet.jsp.tagext.Tag.EVAL_BODY_INCLUDE) {
                          out = _jspx_page_context.popBody();
                        }
                      }
                      if (_jspx_th_html_submit_2.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                        _jspx_tagPool_html_submit_value_styleClass_property_onclick.reuse(_jspx_th_html_submit_2);
                        return;
                      }
                      _jspx_tagPool_html_submit_value_styleClass_property_onclick.reuse(_jspx_th_html_submit_2);
                      out.write("\t\r\n\t\t\t\t\t");
                      int evalDoAfterBody = _jspx_th_logic_equal_6.doAfterBody();
                      if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                        break;
                    } while (true);
                  }
                  if (_jspx_th_logic_equal_6.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                    _jspx_tagPool_logic_equal_value_name.reuse(_jspx_th_logic_equal_6);
                    return;
                  }
                  _jspx_tagPool_logic_equal_value_name.reuse(_jspx_th_logic_equal_6);
                  out.write("\r\n\t\t\t\t\t\r\n\t\t\t\t");
                  int evalDoAfterBody = _jspx_th_html_form_0.doAfterBody();
                  if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                    break;
                } while (true);
              }
              if (_jspx_th_html_form_0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                _jspx_tagPool_html_form_styleId_styleClass_action.reuse(_jspx_th_html_form_0);
                return;
              }
              _jspx_tagPool_html_form_styleId_styleClass_action.reuse(_jspx_th_html_form_0);
              out.write("\r\n\t\t\t");
              int evalDoAfterBody = _jspx_th_logic_equal_0.doAfterBody();
              if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                break;
            } while (true);
          }
          if (_jspx_th_logic_equal_0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
            _jspx_tagPool_logic_equal_value_name.reuse(_jspx_th_logic_equal_0);
            return;
          }
          _jspx_tagPool_logic_equal_value_name.reuse(_jspx_th_logic_equal_0);
          out.write("\r\n\r\n\t\t</div>\r\n\t</div>\r\n\r\n\t\t\t<script type=\"text/javascript\">\r\n\t\t\t\t$(\"#contentSrvConfig form\").submit(function(){\r\n\t\t\t\t\treturn nablifeValidateDialogConfig(); \r\n\t\t\t\t});\r\n\t\t\t</script>\r\n\r\n");
          int evalDoAfterBody = _jspx_th_logic_lessEqual_0.doAfterBody();
          if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
            break;
        } while (true);
      }
      if (_jspx_th_logic_lessEqual_0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
        _jspx_tagPool_logic_lessEqual_value_name.reuse(_jspx_th_logic_lessEqual_0);
        return;
      }
      _jspx_tagPool_logic_lessEqual_value_name.reuse(_jspx_th_logic_lessEqual_0);
    } catch (Throwable t) {
      if (!(t instanceof SkipPageException)){
        out = _jspx_out;
        if (out != null && out.getBufferSize() != 0)
          out.clearBuffer();
        if (_jspx_page_context != null) _jspx_page_context.handlePageException(t);
      }
    } finally {
      if (_jspxFactory != null) _jspxFactory.releasePageContext(_jspx_page_context);
    }
  }

  private boolean _jspx_meth_html_hidden_1(javax.servlet.jsp.tagext.JspTag _jspx_th_html_form_0, PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  html:hidden
    org.apache.struts.taglib.html.HiddenTag _jspx_th_html_hidden_1 = (org.apache.struts.taglib.html.HiddenTag) _jspx_tagPool_html_hidden_value_styleId_property_nobody.get(org.apache.struts.taglib.html.HiddenTag.class);
    _jspx_th_html_hidden_1.setPageContext(_jspx_page_context);
    _jspx_th_html_hidden_1.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_form_0);
    _jspx_th_html_hidden_1.setStyleId("dispatchConfig");
    _jspx_th_html_hidden_1.setProperty("dispatch");
    _jspx_th_html_hidden_1.setValue("load");
    int _jspx_eval_html_hidden_1 = _jspx_th_html_hidden_1.doStartTag();
    if (_jspx_th_html_hidden_1.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _jspx_tagPool_html_hidden_value_styleId_property_nobody.reuse(_jspx_th_html_hidden_1);
      return true;
    }
    _jspx_tagPool_html_hidden_value_styleId_property_nobody.reuse(_jspx_th_html_hidden_1);
    return false;
  }

  private boolean _jspx_meth_logic_equal_1(javax.servlet.jsp.tagext.JspTag _jspx_th_html_form_0, PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  logic:equal
    org.apache.struts.taglib.logic.EqualTag _jspx_th_logic_equal_1 = (org.apache.struts.taglib.logic.EqualTag) _jspx_tagPool_logic_equal_value_name.get(org.apache.struts.taglib.logic.EqualTag.class);
    _jspx_th_logic_equal_1.setPageContext(_jspx_page_context);
    _jspx_th_logic_equal_1.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_form_0);
    _jspx_th_logic_equal_1.setName("error_dne");
    _jspx_th_logic_equal_1.setValue("1");
    int _jspx_eval_logic_equal_1 = _jspx_th_logic_equal_1.doStartTag();
    if (_jspx_eval_logic_equal_1 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
      do {
        out.write("\r\n\t\t\t\t\t\t<script type=\"text/javascript\">\t\t\r\n\t\t\t\t\t\t\tgSrvErrorFlag = true;\r\n\t\t\t\t\t\t\tvar errorMsg = msg_txt['dialog_bad_pseudo'];\r\n\t\t\t\t\t\t\tcustomAlertN(errorMsg);\r\n\t\t\t\t\t\t</script>\r\n\t\t\t\t\t");
        int evalDoAfterBody = _jspx_th_logic_equal_1.doAfterBody();
        if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
          break;
      } while (true);
    }
    if (_jspx_th_logic_equal_1.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _jspx_tagPool_logic_equal_value_name.reuse(_jspx_th_logic_equal_1);
      return true;
    }
    _jspx_tagPool_logic_equal_value_name.reuse(_jspx_th_logic_equal_1);
    return false;
  }

  private boolean _jspx_meth_logic_equal_2(javax.servlet.jsp.tagext.JspTag _jspx_th_html_form_0, PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  logic:equal
    org.apache.struts.taglib.logic.EqualTag _jspx_th_logic_equal_2 = (org.apache.struts.taglib.logic.EqualTag) _jspx_tagPool_logic_equal_value_name.get(org.apache.struts.taglib.logic.EqualTag.class);
    _jspx_th_logic_equal_2.setPageContext(_jspx_page_context);
    _jspx_th_logic_equal_2.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_form_0);
    _jspx_th_logic_equal_2.setName("error_same");
    _jspx_th_logic_equal_2.setValue("1");
    int _jspx_eval_logic_equal_2 = _jspx_th_logic_equal_2.doStartTag();
    if (_jspx_eval_logic_equal_2 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
      do {
        out.write("\r\n\t\t\t\t\t\t<script type=\"text/javascript\">\t\t\r\n\t\t\t\t\t\t\tgSrvErrorFlag = true;\r\n\t\t\t\t\t\t\tvar errorMsg = msg_txt['dialog_cest_toi'];\r\n\t\t\t\t\t\t\tcustomAlertN(errorMsg);\t\t\t\t\r\n\t\t\t\t\t\t</script>\r\n\t\t\t\t\t");
        int evalDoAfterBody = _jspx_th_logic_equal_2.doAfterBody();
        if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
          break;
      } while (true);
    }
    if (_jspx_th_logic_equal_2.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _jspx_tagPool_logic_equal_value_name.reuse(_jspx_th_logic_equal_2);
      return true;
    }
    _jspx_tagPool_logic_equal_value_name.reuse(_jspx_th_logic_equal_2);
    return false;
  }

  private boolean _jspx_meth_html_text_0(javax.servlet.jsp.tagext.JspTag _jspx_th_logic_equal_4, PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  html:text
    org.apache.struts.taglib.html.TextTag _jspx_th_html_text_0 = (org.apache.struts.taglib.html.TextTag) _jspx_tagPool_html_text_styleId_property_name_nobody.get(org.apache.struts.taglib.html.TextTag.class);
    _jspx_th_html_text_0.setPageContext(_jspx_page_context);
    _jspx_th_html_text_0.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_equal_4);
    _jspx_th_html_text_0.setName("mySrvDialogForm");
    _jspx_th_html_text_0.setProperty("friendName");
    _jspx_th_html_text_0.setStyleId("friendName");
    int _jspx_eval_html_text_0 = _jspx_th_html_text_0.doStartTag();
    if (_jspx_th_html_text_0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _jspx_tagPool_html_text_styleId_property_name_nobody.reuse(_jspx_th_html_text_0);
      return true;
    }
    _jspx_tagPool_html_text_styleId_property_name_nobody.reuse(_jspx_th_html_text_0);
    return false;
  }
}
