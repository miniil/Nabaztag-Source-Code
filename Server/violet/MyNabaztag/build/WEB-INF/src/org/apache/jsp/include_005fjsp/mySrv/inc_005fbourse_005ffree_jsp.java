package org.apache.jsp.include_005fjsp.mySrv;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import net.violet.platform.util.StaticTools;
import net.violet.platform.util.SessionTools;
import net.violet.platform.datamodel.Lang;
import net.violet.platform.util.DicoTools;
import net.violet.platform.util.MyConstantes;

public final class inc_005fbourse_005ffree_jsp extends org.apache.jasper.runtime.HttpJspBase
    implements org.apache.jasper.runtime.JspSourceDependent {

  private static java.util.List _jspx_dependants;

  static {
    _jspx_dependants = new java.util.ArrayList(1);
    _jspx_dependants.add("/include_jsp/utils/inc_dico.jsp");
  }

  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_bean_define_property_name_id_nobody;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_bean_define_type_property_name_id_nobody;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_html_form_styleId_styleClass_action;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_bean_define_value_id_nobody;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_html_select_styleId_property_name;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_html_optionsCollection_value_property_name_label_nobody;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_logic_equal_value_name;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_html_checkbox_value_styleId_property_name_nobody;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_html_hidden_value_styleId_property_nobody;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_logic_notEqual_value_name;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_html_button_value_styleClass_property_onclick;
  private org.apache.jasper.runtime.TagHandlerPool _jspx_tagPool_html_submit_value_styleClass_property_onclick;

  public Object getDependants() {
    return _jspx_dependants;
  }

  public void _jspInit() {
    _jspx_tagPool_bean_define_property_name_id_nobody = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_bean_define_type_property_name_id_nobody = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_html_form_styleId_styleClass_action = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_bean_define_value_id_nobody = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_html_select_styleId_property_name = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_html_optionsCollection_value_property_name_label_nobody = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_logic_equal_value_name = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_html_checkbox_value_styleId_property_name_nobody = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_html_hidden_value_styleId_property_nobody = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_logic_notEqual_value_name = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_html_button_value_styleClass_property_onclick = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
    _jspx_tagPool_html_submit_value_styleClass_property_onclick = org.apache.jasper.runtime.TagHandlerPool.getTagHandlerPool(getServletConfig());
  }

  public void _jspDestroy() {
    _jspx_tagPool_bean_define_property_name_id_nobody.release();
    _jspx_tagPool_bean_define_type_property_name_id_nobody.release();
    _jspx_tagPool_html_form_styleId_styleClass_action.release();
    _jspx_tagPool_bean_define_value_id_nobody.release();
    _jspx_tagPool_html_select_styleId_property_name.release();
    _jspx_tagPool_html_optionsCollection_value_property_name_label_nobody.release();
    _jspx_tagPool_logic_equal_value_name.release();
    _jspx_tagPool_html_checkbox_value_styleId_property_name_nobody.release();
    _jspx_tagPool_html_hidden_value_styleId_property_nobody.release();
    _jspx_tagPool_logic_notEqual_value_name.release();
    _jspx_tagPool_html_button_value_styleClass_property_onclick.release();
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

      out.write("\n\r\n\r\n");
 response.setContentType("text/html;charset=UTF-8"); 
      out.write("\r\n\n\r\n\r\n\r\n\r\n\r\n");
      out.write('\n');
      out.write('\r');
      out.write('\n');
      out.write("\r\n\r\n\n");
	Lang dico_lang = SessionTools.getLangFromSession(session, request);
      out.write("\r\n\r\n");
      //  bean:define
      org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_0 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
      _jspx_th_bean_define_0.setPageContext(_jspx_page_context);
      _jspx_th_bean_define_0.setParent(null);
      _jspx_th_bean_define_0.setProperty("isReg");
      _jspx_th_bean_define_0.setName("mySrvBourseFreeForm");
      _jspx_th_bean_define_0.setId("isReg");
      int _jspx_eval_bean_define_0 = _jspx_th_bean_define_0.doStartTag();
      if (_jspx_th_bean_define_0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
        _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_0);
        return;
      }
      _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_0);
      java.lang.Object isReg = null;
      isReg = (java.lang.Object) _jspx_page_context.findAttribute("isReg");
      out.write('\r');
      out.write('\n');
      //  bean:define
      org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_1 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_type_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
      _jspx_th_bean_define_1.setPageContext(_jspx_page_context);
      _jspx_th_bean_define_1.setParent(null);
      _jspx_th_bean_define_1.setProperty("serviceName");
      _jspx_th_bean_define_1.setName("mySrvBourseFreeForm");
      _jspx_th_bean_define_1.setId("serviceName");
      _jspx_th_bean_define_1.setType("String");
      int _jspx_eval_bean_define_1 = _jspx_th_bean_define_1.doStartTag();
      if (_jspx_th_bean_define_1.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
        _jspx_tagPool_bean_define_type_property_name_id_nobody.reuse(_jspx_th_bean_define_1);
        return;
      }
      _jspx_tagPool_bean_define_type_property_name_id_nobody.reuse(_jspx_th_bean_define_1);
      String serviceName = null;
      serviceName = (String) _jspx_page_context.findAttribute("serviceName");
      out.write("\r\n\r\n<div class=\"main-cadre-contener\">\r\n\t<div class=\"main-cadre-top\"><h2>");
      out.print(DicoTools.dico(dico_lang , "services/configure"));
      out.write("</h2></div>\r\n\t<div class=\"main-cadre-content\">\r\n\t\t<hr class=\"spacer\"/>\r\n\t\t<!-- ******************************************** CONTENT ***************************************************** --> \r\n\t\t<div class=\"srv-main-config\" >\r\n\t\t\t<hr class=\"spacer\" />\r\n\t\t\t<!-- \r\n\t\t\t<div id=\"description-srv\">\r\n\t\t\t\t\r\n\t\t\t\t<p class=\"short-desc\">");
      out.print(DicoTools.dico(dico_lang , "srv_bourse_free/description"));
      out.write("</p>\r\n\t\t\t\t<p class=\"long-desc\">");
      out.print(DicoTools.dico(dico_lang , "srv_bourse_free/long_description"));
      out.write("</p>\r\n\t\t\t</div>\r\n\t\t\t\r\n\t\t\t<hr class=\"spacer\" />\r\n\t\t\t-->\t\t\t\t\t\r\n\t\t\t");
      //  html:form
      org.apache.struts.taglib.html.FormTag _jspx_th_html_form_0 = (org.apache.struts.taglib.html.FormTag) _jspx_tagPool_html_form_styleId_styleClass_action.get(org.apache.struts.taglib.html.FormTag.class);
      _jspx_th_html_form_0.setPageContext(_jspx_page_context);
      _jspx_th_html_form_0.setParent(null);
      _jspx_th_html_form_0.setAction("/action/srvBourseFreeConfig");
      _jspx_th_html_form_0.setStyleId("srvBourseFreeConfig");
      _jspx_th_html_form_0.setStyleClass("srvConfigForm");
      int _jspx_eval_html_form_0 = _jspx_th_html_form_0.doStartTag();
      if (_jspx_eval_html_form_0 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
        do {
          out.write("\r\n\t\t\t\t\r\n\t\t\t\t");
          //  bean:define
          org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_2 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
          _jspx_th_bean_define_2.setPageContext(_jspx_page_context);
          _jspx_th_bean_define_2.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_form_0);
          _jspx_th_bean_define_2.setName("mySrvBourseFreeForm");
          _jspx_th_bean_define_2.setProperty("horraire1");
          _jspx_th_bean_define_2.setId("heures1");
          int _jspx_eval_bean_define_2 = _jspx_th_bean_define_2.doStartTag();
          if (_jspx_th_bean_define_2.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
            _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_2);
            return;
          }
          _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_2);
          java.lang.Object heures1 = null;
          heures1 = (java.lang.Object) _jspx_page_context.findAttribute("heures1");
          out.write("\r\n\t\t\t\t");
          //  bean:define
          org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_3 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_property_name_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
          _jspx_th_bean_define_3.setPageContext(_jspx_page_context);
          _jspx_th_bean_define_3.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_form_0);
          _jspx_th_bean_define_3.setName("mySrvBourseFreeForm");
          _jspx_th_bean_define_3.setProperty("horraire2");
          _jspx_th_bean_define_3.setId("heures2");
          int _jspx_eval_bean_define_3 = _jspx_th_bean_define_3.doStartTag();
          if (_jspx_th_bean_define_3.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
            _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_3);
            return;
          }
          _jspx_tagPool_bean_define_property_name_id_nobody.reuse(_jspx_th_bean_define_3);
          java.lang.Object heures2 = null;
          heures2 = (java.lang.Object) _jspx_page_context.findAttribute("heures2");
          out.write("\r\n\t\t\t\t");
          //  bean:define
          org.apache.struts.taglib.bean.DefineTag _jspx_th_bean_define_4 = (org.apache.struts.taglib.bean.DefineTag) _jspx_tagPool_bean_define_value_id_nobody.get(org.apache.struts.taglib.bean.DefineTag.class);
          _jspx_th_bean_define_4.setPageContext(_jspx_page_context);
          _jspx_th_bean_define_4.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_form_0);
          _jspx_th_bean_define_4.setId("flashActivated");
          _jspx_th_bean_define_4.setValue(( !heures1.equals("") || !heures2.equals("") ) ? "true" : "false" );
          int _jspx_eval_bean_define_4 = _jspx_th_bean_define_4.doStartTag();
          if (_jspx_th_bean_define_4.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
            _jspx_tagPool_bean_define_value_id_nobody.reuse(_jspx_th_bean_define_4);
            return;
          }
          _jspx_tagPool_bean_define_value_id_nobody.reuse(_jspx_th_bean_define_4);
          java.lang.String flashActivated = null;
          flashActivated = (java.lang.String) _jspx_page_context.findAttribute("flashActivated");
          out.write("\r\n\t\t\t\t\t\t\t\r\n\t\t\t\t<table class=\"table-serv-conf\">\r\n\t\t\t\t\t\r\n\t\t\t\t\t<tr>\r\n\t\t\t\t\t\t<th>\r\n\t\t\t\t\t\t\t");
          out.print(DicoTools.dico(dico_lang , "srv_bourse/choose_index"));
          out.write("\r\n\t\t\t\t\t\t</th>\r\n\t\t\t\t\t\t<td>\r\n\t\t\t\t\t\t\t");
          if (_jspx_meth_html_select_0(_jspx_th_html_form_0, _jspx_page_context))
            return;
          out.write("\r\n\t\t\t\t\t\t</td>\r\n\t\t\t\t\t</tr>\r\n\t\t\t\t\t\r\n\t\t\t\t\t<tr class=\"flash\">\r\n\t\t\t\t\t\t<th>\r\n\t\t\t\t\t\t\t");
          out.print(DicoTools.dico(dico_lang , "service/flash_audio"));
          out.write("\r\n\t\t\t\t\t\t</th>\r\n\t\t\t\t\t\t<td>\r\n\t\t\t\t\t\t\t<div class=\"b_checkactivate checkactivate\">\r\n\t\t\t\t\t\t\t\t\r\n\t\t\t\t\t\t\t\t<div class=\"check\">\r\n\t\t\t\t\t\t\t\t\t<label class=\"lab\">\r\n\t\t\t\t\t\t\t\t\t\t<input type=\"checkbox\" ");
          if (_jspx_meth_logic_equal_0(_jspx_th_html_form_0, _jspx_page_context))
            return;
          out.write(" />\r\n\t\t\t\t\t\t\t\t\t\t");
          out.print(DicoTools.dico(dico_lang , "service/activate"));
          out.write("\r\n\t\t\t\t\t\t\t\t\t</label>\r\n\t\t\t\t\t\t\t\t</div>\r\n\t\t\t\t\t\t\t\t\r\n\t\t\t\t\t\t\t\t<div class=\"content\">\t\t\r\n\t\t\t\t\t\t\t\t\t\t\t\t\t\r\n\t\t\t\t\t\t\t\t\t<div class=\"contener\">\r\n\t\t\t\t\t\t\t\t\t\t<span class=\"label\" >");
          out.print(DicoTools.dico(dico_lang , "service/first_flash"));
          out.write("</span><input id=\"time1\" name=\"horraire1\" type=\"hidden\" class=\"hourPicker\" value=\"");
          out.print(heures1);
          out.write("\" />\r\n\t\t\t\t\t\t\t\t\t</div>\r\n\t\t\t\t\t\t\t\t\t\r\n\t\t\t\t\t\t\t\t\t<div class=\"contener\">\r\n\t\t\t\t\t\t\t\t\t\t<span class=\"label\" >");
          out.print(DicoTools.dico(dico_lang , "service/second_flash"));
          out.write("</span><input id=\"time2\" name=\"horraire2\" type=\"hidden\" class=\"hourPicker\" value=\"");
          out.print(heures2);
          out.write("\" />\r\n\t\t\t\t\t\t\t\t\t</div>\r\n\t\t\t\t\t\t\t\t\t\r\n\t\t\t\t\t\t\t\t\t<hr class=\"clearer\" />\r\n\t\t\t\t\t\t\t\t\t\r\n\t\t\t\t\t\t\t\t\t<div style=\"clear:both; margin:6px 0;\">\r\n\t\t\t\t\t\t\t\t\t\t<label>");
          if (_jspx_meth_html_checkbox_0(_jspx_th_html_form_0, _jspx_page_context))
            return;
          out.print(DicoTools.dico(dico_lang , "srv_bourse/deactivate_week_end"));
          out.write("</label>\r\n\t\t\t\t\t\t\t\t\t</div>\r\n\t\t\t\t\t\t\t\t\t\r\n\t\t\t\t\t\t\t\t</div>\r\n\t\t\t\t\t\t\t\t\r\n\t\t\t\t\t\t\t</div>\r\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\r\n\t\t\t\t\t\t</td>\r\n\t\t\t\t\t</tr>\r\n\r\n\t\t\t\t\t<tr class=\"lights\">\r\n\t\t\t\t\t\t<th>\r\n\t\t\t\t\t\t\t");
          out.print(DicoTools.dico(dico_lang , "srv_bourse/light_language"));
          out.write("\r\n\t\t\t\t\t\t</th>\r\n\t\t\t\t\t\t<td>\r\n\t\t\t\t\t\t\t");
          if (_jspx_meth_html_checkbox_1(_jspx_th_html_form_0, _jspx_page_context))
            return;
          out.write("\t<a href=\"#keskiditTop\">");
          out.print(DicoTools.dico(dico_lang , "srv_all/light_help"));
          out.write("</a>\t\t\t\t\t\t\t\t\t\t\t\t\r\n\t\t\t\t\t\t</td>\r\n\t\t\t\t\t</tr>\r\n\t\t\t\t\t\t\t\t\t\t\r\n\t\t\t\t\t\t\t\t\t\t\r\n\t\t\t\t\t<tr class=\"reco\">\r\n\t\t\t\t\t\t<th>\r\n\t\t\t\t\t\t\t");
          out.print(DicoTools.dico(dico_lang , "services/vocal"));
          out.write("\r\n\t\t\t\t\t\t</th>\r\n\t\t\t\t\t\t<td>\r\n\t\t\t\t\t\t\t<span style=\"font-size:16px; font-weight:bold;\">");
          out.print(DicoTools.dico(dico_lang , "srv_bourse/vocal"));
          out.write("</span> ");
          out.print(DicoTools.dico(dico_lang , "srv_all/reco_link"));
          out.write("\t\t\t\t\t\t\t\t\t\t\t\r\n\t\t\t\t\t\t</td>\r\n\t\t\t\t\t</tr>\r\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\r\n\t\t\t\t</table>\r\n\t\t\t\r\n\t\t\t\t<hr class=\"spacer\" />\r\n\t\t\t\t\t\t\r\n\t\t\t\t");
          if (_jspx_meth_html_hidden_0(_jspx_th_html_form_0, _jspx_page_context))
            return;
          out.write("\r\n\t\t\t\r\n\t\t\t\r\n\t\t\t\t<div align=\"center\">\r\n\t\t\t\t\t");
/* Supression */
          out.write("\t\t\r\n\t\t\t\t\t");
          //  logic:notEqual
          org.apache.struts.taglib.logic.NotEqualTag _jspx_th_logic_notEqual_0 = (org.apache.struts.taglib.logic.NotEqualTag) _jspx_tagPool_logic_notEqual_value_name.get(org.apache.struts.taglib.logic.NotEqualTag.class);
          _jspx_th_logic_notEqual_0.setPageContext(_jspx_page_context);
          _jspx_th_logic_notEqual_0.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_form_0);
          _jspx_th_logic_notEqual_0.setName("isReg");
          _jspx_th_logic_notEqual_0.setValue("0");
          int _jspx_eval_logic_notEqual_0 = _jspx_th_logic_notEqual_0.doStartTag();
          if (_jspx_eval_logic_notEqual_0 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
            do {
              out.write("\r\n\t\t\t\t\t\t");
              //  html:button
              org.apache.struts.taglib.html.ButtonTag _jspx_th_html_button_0 = (org.apache.struts.taglib.html.ButtonTag) _jspx_tagPool_html_button_value_styleClass_property_onclick.get(org.apache.struts.taglib.html.ButtonTag.class);
              _jspx_th_html_button_0.setPageContext(_jspx_page_context);
              _jspx_th_html_button_0.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_notEqual_0);
              _jspx_th_html_button_0.setProperty("delete");
              _jspx_th_html_button_0.setValue(DicoTools.dico(dico_lang , "srv_bourse/button_delete"));
              _jspx_th_html_button_0.setStyleClass("genericDeleteBt");
              _jspx_th_html_button_0.setOnclick("serviceDelete();");
              int _jspx_eval_html_button_0 = _jspx_th_html_button_0.doStartTag();
              if (_jspx_eval_html_button_0 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
                if (_jspx_eval_html_button_0 != javax.servlet.jsp.tagext.Tag.EVAL_BODY_INCLUDE) {
                  out = _jspx_page_context.pushBody();
                  _jspx_th_html_button_0.setBodyContent((javax.servlet.jsp.tagext.BodyContent) out);
                  _jspx_th_html_button_0.doInitBody();
                }
                do {
                  out.print(DicoTools.dico(dico_lang , "srv_bourse/button_delete"));
                  int evalDoAfterBody = _jspx_th_html_button_0.doAfterBody();
                  if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                    break;
                } while (true);
                if (_jspx_eval_html_button_0 != javax.servlet.jsp.tagext.Tag.EVAL_BODY_INCLUDE) {
                  out = _jspx_page_context.popBody();
                }
              }
              if (_jspx_th_html_button_0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
                _jspx_tagPool_html_button_value_styleClass_property_onclick.reuse(_jspx_th_html_button_0);
                return;
              }
              _jspx_tagPool_html_button_value_styleClass_property_onclick.reuse(_jspx_th_html_button_0);
              out.write("\r\n\t\t\t\t\t");
              int evalDoAfterBody = _jspx_th_logic_notEqual_0.doAfterBody();
              if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                break;
            } while (true);
          }
          if (_jspx_th_logic_notEqual_0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
            _jspx_tagPool_logic_notEqual_value_name.reuse(_jspx_th_logic_notEqual_0);
            return;
          }
          _jspx_tagPool_logic_notEqual_value_name.reuse(_jspx_th_logic_notEqual_0);
          out.write("\r\n\t\t\t\t\t\r\n\t\t\t\t\t");
/* Creation */
          out.write("\r\n\t\t\t\t\t");
          //  logic:equal
          org.apache.struts.taglib.logic.EqualTag _jspx_th_logic_equal_1 = (org.apache.struts.taglib.logic.EqualTag) _jspx_tagPool_logic_equal_value_name.get(org.apache.struts.taglib.logic.EqualTag.class);
          _jspx_th_logic_equal_1.setPageContext(_jspx_page_context);
          _jspx_th_logic_equal_1.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_form_0);
          _jspx_th_logic_equal_1.setName("isReg");
          _jspx_th_logic_equal_1.setValue("0");
          int _jspx_eval_logic_equal_1 = _jspx_th_logic_equal_1.doStartTag();
          if (_jspx_eval_logic_equal_1 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
            do {
              out.write("\r\n\t\t\t\t\t\t");
              //  html:submit
              org.apache.struts.taglib.html.SubmitTag _jspx_th_html_submit_0 = (org.apache.struts.taglib.html.SubmitTag) _jspx_tagPool_html_submit_value_styleClass_property_onclick.get(org.apache.struts.taglib.html.SubmitTag.class);
              _jspx_th_html_submit_0.setPageContext(_jspx_page_context);
              _jspx_th_html_submit_0.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_equal_1);
              _jspx_th_html_submit_0.setProperty("activate");
              _jspx_th_html_submit_0.setValue(DicoTools.dico(dico_lang , "srv_bourse/button_activate"));
              _jspx_th_html_submit_0.setStyleClass("genericBt");
              _jspx_th_html_submit_0.setOnclick("goDispatch('activate', 'dispatchConfig')");
              int _jspx_eval_html_submit_0 = _jspx_th_html_submit_0.doStartTag();
              if (_jspx_eval_html_submit_0 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
                if (_jspx_eval_html_submit_0 != javax.servlet.jsp.tagext.Tag.EVAL_BODY_INCLUDE) {
                  out = _jspx_page_context.pushBody();
                  _jspx_th_html_submit_0.setBodyContent((javax.servlet.jsp.tagext.BodyContent) out);
                  _jspx_th_html_submit_0.doInitBody();
                }
                do {
                  out.print(DicoTools.dico(dico_lang , "srv_bourse/button_activate"));
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
              out.write("\t\r\n\t\t\t\t\t");
              int evalDoAfterBody = _jspx_th_logic_equal_1.doAfterBody();
              if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                break;
            } while (true);
          }
          if (_jspx_th_logic_equal_1.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
            _jspx_tagPool_logic_equal_value_name.reuse(_jspx_th_logic_equal_1);
            return;
          }
          _jspx_tagPool_logic_equal_value_name.reuse(_jspx_th_logic_equal_1);
          out.write("\r\n\t\t\t\t\t\r\n\t\t\t\t\t");
/* Mise a jour */
          out.write("\t\t\t\r\n\t\t\t\t\t");
          //  logic:notEqual
          org.apache.struts.taglib.logic.NotEqualTag _jspx_th_logic_notEqual_1 = (org.apache.struts.taglib.logic.NotEqualTag) _jspx_tagPool_logic_notEqual_value_name.get(org.apache.struts.taglib.logic.NotEqualTag.class);
          _jspx_th_logic_notEqual_1.setPageContext(_jspx_page_context);
          _jspx_th_logic_notEqual_1.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_form_0);
          _jspx_th_logic_notEqual_1.setName("isReg");
          _jspx_th_logic_notEqual_1.setValue("0");
          int _jspx_eval_logic_notEqual_1 = _jspx_th_logic_notEqual_1.doStartTag();
          if (_jspx_eval_logic_notEqual_1 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
            do {
              out.write("\r\n\t\t\t\t\t\t");
              //  html:submit
              org.apache.struts.taglib.html.SubmitTag _jspx_th_html_submit_1 = (org.apache.struts.taglib.html.SubmitTag) _jspx_tagPool_html_submit_value_styleClass_property_onclick.get(org.apache.struts.taglib.html.SubmitTag.class);
              _jspx_th_html_submit_1.setPageContext(_jspx_page_context);
              _jspx_th_html_submit_1.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_logic_notEqual_1);
              _jspx_th_html_submit_1.setProperty("update");
              _jspx_th_html_submit_1.setValue(DicoTools.dico(dico_lang , "srv_bourse/button_update"));
              _jspx_th_html_submit_1.setStyleClass("genericBt");
              _jspx_th_html_submit_1.setOnclick("goDispatch('update', 'dispatchConfig')");
              int _jspx_eval_html_submit_1 = _jspx_th_html_submit_1.doStartTag();
              if (_jspx_eval_html_submit_1 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
                if (_jspx_eval_html_submit_1 != javax.servlet.jsp.tagext.Tag.EVAL_BODY_INCLUDE) {
                  out = _jspx_page_context.pushBody();
                  _jspx_th_html_submit_1.setBodyContent((javax.servlet.jsp.tagext.BodyContent) out);
                  _jspx_th_html_submit_1.doInitBody();
                }
                do {
                  out.print(DicoTools.dico(dico_lang , "srv_bourse/button_update"));
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
              out.write("\r\n\t\t\t\t\t");
              int evalDoAfterBody = _jspx_th_logic_notEqual_1.doAfterBody();
              if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
                break;
            } while (true);
          }
          if (_jspx_th_logic_notEqual_1.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
            _jspx_tagPool_logic_notEqual_value_name.reuse(_jspx_th_logic_notEqual_1);
            return;
          }
          _jspx_tagPool_logic_notEqual_value_name.reuse(_jspx_th_logic_notEqual_1);
          out.write("\r\n\t\t\t\t</div>\r\n\t\t\t\t\r\n\t\t\t");
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
      out.write("\r\n\t\t</div>\r\n\t\t\r\n\t\t<hr class=\"spacer\" />\t\t\t\r\n\t\t<!-- ******************************************** /CONTENT ***************************************************** -->        \r\n\t</div>\r\n</div>\r\n\r\n<script type=\"text/javascript\">\r\n\t\r\n\t$(\"input.hourPicker\").hourSelect_InitN(false );\r\n\t\t\r\n\t$(\"#list\").select_NotclickableValues();\r\n\t\t\r\n\t$(\"#contentSrvConfig form\").submit(function(){\r\n\t\treturn nablifeValidateBourseFreeConfig(");
      if (_jspx_meth_logic_equal_2(_jspx_page_context))
        return;
      out.write("); \r\n\t});\r\n\t\r\n\tsrvTableInit(); // active le roll over sur les TR\r\n\t$(\"div.b_checkactivate\").checkactivate();\r\n\r\n</script>\r\n\r\n");
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

  private boolean _jspx_meth_html_select_0(javax.servlet.jsp.tagext.JspTag _jspx_th_html_form_0, PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  html:select
    org.apache.struts.taglib.html.SelectTag _jspx_th_html_select_0 = (org.apache.struts.taglib.html.SelectTag) _jspx_tagPool_html_select_styleId_property_name.get(org.apache.struts.taglib.html.SelectTag.class);
    _jspx_th_html_select_0.setPageContext(_jspx_page_context);
    _jspx_th_html_select_0.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_form_0);
    _jspx_th_html_select_0.setName("mySrvBourseFreeForm");
    _jspx_th_html_select_0.setProperty("indic");
    _jspx_th_html_select_0.setStyleId("list");
    int _jspx_eval_html_select_0 = _jspx_th_html_select_0.doStartTag();
    if (_jspx_eval_html_select_0 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
      if (_jspx_eval_html_select_0 != javax.servlet.jsp.tagext.Tag.EVAL_BODY_INCLUDE) {
        out = _jspx_page_context.pushBody();
        _jspx_th_html_select_0.setBodyContent((javax.servlet.jsp.tagext.BodyContent) out);
        _jspx_th_html_select_0.doInitBody();
      }
      do {
        out.write("\r\n\t\t\t\t\t\t\t\t<option value=\"\"></option>\n\t\t\t\t\t\t\t\t<!--  FrequenceData -->\t\r\n\t\t\t\t\t\t\t\t");
        if (_jspx_meth_html_optionsCollection_0(_jspx_th_html_select_0, _jspx_page_context))
          return true;
        out.write("\r\n\t\t\t\t\t\t\t");
        int evalDoAfterBody = _jspx_th_html_select_0.doAfterBody();
        if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
          break;
      } while (true);
      if (_jspx_eval_html_select_0 != javax.servlet.jsp.tagext.Tag.EVAL_BODY_INCLUDE) {
        out = _jspx_page_context.popBody();
      }
    }
    if (_jspx_th_html_select_0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _jspx_tagPool_html_select_styleId_property_name.reuse(_jspx_th_html_select_0);
      return true;
    }
    _jspx_tagPool_html_select_styleId_property_name.reuse(_jspx_th_html_select_0);
    return false;
  }

  private boolean _jspx_meth_html_optionsCollection_0(javax.servlet.jsp.tagext.JspTag _jspx_th_html_select_0, PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  html:optionsCollection
    org.apache.struts.taglib.html.OptionsCollectionTag _jspx_th_html_optionsCollection_0 = (org.apache.struts.taglib.html.OptionsCollectionTag) _jspx_tagPool_html_optionsCollection_value_property_name_label_nobody.get(org.apache.struts.taglib.html.OptionsCollectionTag.class);
    _jspx_th_html_optionsCollection_0.setPageContext(_jspx_page_context);
    _jspx_th_html_optionsCollection_0.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_select_0);
    _jspx_th_html_optionsCollection_0.setName("mySrvBourseFreeForm");
    _jspx_th_html_optionsCollection_0.setProperty("indicList");
    _jspx_th_html_optionsCollection_0.setLabel("label");
    _jspx_th_html_optionsCollection_0.setValue("id");
    int _jspx_eval_html_optionsCollection_0 = _jspx_th_html_optionsCollection_0.doStartTag();
    if (_jspx_th_html_optionsCollection_0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _jspx_tagPool_html_optionsCollection_value_property_name_label_nobody.reuse(_jspx_th_html_optionsCollection_0);
      return true;
    }
    _jspx_tagPool_html_optionsCollection_value_property_name_label_nobody.reuse(_jspx_th_html_optionsCollection_0);
    return false;
  }

  private boolean _jspx_meth_logic_equal_0(javax.servlet.jsp.tagext.JspTag _jspx_th_html_form_0, PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  logic:equal
    org.apache.struts.taglib.logic.EqualTag _jspx_th_logic_equal_0 = (org.apache.struts.taglib.logic.EqualTag) _jspx_tagPool_logic_equal_value_name.get(org.apache.struts.taglib.logic.EqualTag.class);
    _jspx_th_logic_equal_0.setPageContext(_jspx_page_context);
    _jspx_th_logic_equal_0.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_form_0);
    _jspx_th_logic_equal_0.setValue("true");
    _jspx_th_logic_equal_0.setName("flashActivated");
    int _jspx_eval_logic_equal_0 = _jspx_th_logic_equal_0.doStartTag();
    if (_jspx_eval_logic_equal_0 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
      do {
        out.write("checked=\"checked\"");
        int evalDoAfterBody = _jspx_th_logic_equal_0.doAfterBody();
        if (evalDoAfterBody != javax.servlet.jsp.tagext.BodyTag.EVAL_BODY_AGAIN)
          break;
      } while (true);
    }
    if (_jspx_th_logic_equal_0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _jspx_tagPool_logic_equal_value_name.reuse(_jspx_th_logic_equal_0);
      return true;
    }
    _jspx_tagPool_logic_equal_value_name.reuse(_jspx_th_logic_equal_0);
    return false;
  }

  private boolean _jspx_meth_html_checkbox_0(javax.servlet.jsp.tagext.JspTag _jspx_th_html_form_0, PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  html:checkbox
    org.apache.struts.taglib.html.CheckboxTag _jspx_th_html_checkbox_0 = (org.apache.struts.taglib.html.CheckboxTag) _jspx_tagPool_html_checkbox_value_styleId_property_name_nobody.get(org.apache.struts.taglib.html.CheckboxTag.class);
    _jspx_th_html_checkbox_0.setPageContext(_jspx_page_context);
    _jspx_th_html_checkbox_0.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_form_0);
    _jspx_th_html_checkbox_0.setName("mySrvBourseFreeForm");
    _jspx_th_html_checkbox_0.setProperty("weekend");
    _jspx_th_html_checkbox_0.setValue("1");
    _jspx_th_html_checkbox_0.setStyleId("weekend");
    int _jspx_eval_html_checkbox_0 = _jspx_th_html_checkbox_0.doStartTag();
    if (_jspx_th_html_checkbox_0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _jspx_tagPool_html_checkbox_value_styleId_property_name_nobody.reuse(_jspx_th_html_checkbox_0);
      return true;
    }
    _jspx_tagPool_html_checkbox_value_styleId_property_name_nobody.reuse(_jspx_th_html_checkbox_0);
    return false;
  }

  private boolean _jspx_meth_html_checkbox_1(javax.servlet.jsp.tagext.JspTag _jspx_th_html_form_0, PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  html:checkbox
    org.apache.struts.taglib.html.CheckboxTag _jspx_th_html_checkbox_1 = (org.apache.struts.taglib.html.CheckboxTag) _jspx_tagPool_html_checkbox_value_styleId_property_name_nobody.get(org.apache.struts.taglib.html.CheckboxTag.class);
    _jspx_th_html_checkbox_1.setPageContext(_jspx_page_context);
    _jspx_th_html_checkbox_1.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_form_0);
    _jspx_th_html_checkbox_1.setName("mySrvBourseFreeForm");
    _jspx_th_html_checkbox_1.setProperty("lumiere");
    _jspx_th_html_checkbox_1.setValue("1");
    _jspx_th_html_checkbox_1.setStyleId("lumiere");
    int _jspx_eval_html_checkbox_1 = _jspx_th_html_checkbox_1.doStartTag();
    if (_jspx_th_html_checkbox_1.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _jspx_tagPool_html_checkbox_value_styleId_property_name_nobody.reuse(_jspx_th_html_checkbox_1);
      return true;
    }
    _jspx_tagPool_html_checkbox_value_styleId_property_name_nobody.reuse(_jspx_th_html_checkbox_1);
    return false;
  }

  private boolean _jspx_meth_html_hidden_0(javax.servlet.jsp.tagext.JspTag _jspx_th_html_form_0, PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  html:hidden
    org.apache.struts.taglib.html.HiddenTag _jspx_th_html_hidden_0 = (org.apache.struts.taglib.html.HiddenTag) _jspx_tagPool_html_hidden_value_styleId_property_nobody.get(org.apache.struts.taglib.html.HiddenTag.class);
    _jspx_th_html_hidden_0.setPageContext(_jspx_page_context);
    _jspx_th_html_hidden_0.setParent((javax.servlet.jsp.tagext.Tag) _jspx_th_html_form_0);
    _jspx_th_html_hidden_0.setStyleId("dispatchConfig");
    _jspx_th_html_hidden_0.setProperty("dispatch");
    _jspx_th_html_hidden_0.setValue("load");
    int _jspx_eval_html_hidden_0 = _jspx_th_html_hidden_0.doStartTag();
    if (_jspx_th_html_hidden_0.doEndTag() == javax.servlet.jsp.tagext.Tag.SKIP_PAGE) {
      _jspx_tagPool_html_hidden_value_styleId_property_nobody.reuse(_jspx_th_html_hidden_0);
      return true;
    }
    _jspx_tagPool_html_hidden_value_styleId_property_nobody.reuse(_jspx_th_html_hidden_0);
    return false;
  }

  private boolean _jspx_meth_logic_equal_2(PageContext _jspx_page_context)
          throws Throwable {
    PageContext pageContext = _jspx_page_context;
    JspWriter out = _jspx_page_context.getOut();
    //  logic:equal
    org.apache.struts.taglib.logic.EqualTag _jspx_th_logic_equal_2 = (org.apache.struts.taglib.logic.EqualTag) _jspx_tagPool_logic_equal_value_name.get(org.apache.struts.taglib.logic.EqualTag.class);
    _jspx_th_logic_equal_2.setPageContext(_jspx_page_context);
    _jspx_th_logic_equal_2.setParent(null);
    _jspx_th_logic_equal_2.setName("isReg");
    _jspx_th_logic_equal_2.setValue("1");
    int _jspx_eval_logic_equal_2 = _jspx_th_logic_equal_2.doStartTag();
    if (_jspx_eval_logic_equal_2 != javax.servlet.jsp.tagext.Tag.SKIP_BODY) {
      do {
        out.write("true");
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
}
