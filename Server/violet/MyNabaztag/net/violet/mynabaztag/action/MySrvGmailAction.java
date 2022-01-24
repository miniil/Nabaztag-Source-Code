package net.violet.mynabaztag.action;

import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import net.violet.mynabaztag.form.MySrvGmailForm;
import net.violet.platform.applications.GmailTwitterHandler;
import net.violet.platform.applications.SubscriptionManager;
import net.violet.platform.datamodel.Application;
import net.violet.platform.datamodel.Lang;
import net.violet.platform.datamodel.User;
import net.violet.platform.datamodel.VObject;
import net.violet.platform.datamodel.factories.Factories;
import net.violet.platform.dataobjects.SubscriptionData;
import net.violet.platform.dataobjects.TtsLangData;
import net.violet.platform.dataobjects.VObjectData;
import net.violet.platform.struts.DispatchActionForLoggedUserWithObject;
import net.violet.platform.util.DicoTools;
import net.violet.platform.util.SessionTools;
import net.violet.platform.util.StringShop;

import org.apache.log4j.Logger;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;

public class MySrvGmailAction extends DispatchActionForLoggedUserWithObject {

	private static final Logger LOGGER = Logger.getLogger(MySrvGmailAction.class);

	public ActionForward load(ActionMapping mapping, ActionForm form, HttpServletRequest request, @SuppressWarnings("unused") HttpServletResponse response) {

		final HttpSession session = request.getSession(true);
		final User user = SessionTools.getUserFromSession(request);
		final VObject object = SessionTools.getRabbitFromSession(session);
		final Lang lang = SessionTools.getLangFromSession(session, request);
		final MySrvGmailForm myForm = (MySrvGmailForm) form;

		final List<SubscriptionData> theSubscriptions = SubscriptionData.findByApplicationAndObject(Application.NativeApplication.GMAIL.getApplication(), object);

		if (!theSubscriptions.isEmpty()) {
			final SubscriptionData theSubscription = theSubscriptions.get(0);
			final Map<String, Object> theSettings = theSubscription.getSettings();
			myForm.setLogin(theSettings.get(GmailTwitterHandler.LOGIN).toString());
			myForm.setPassword(StringShop.EMPTY_STRING);
			final Lang theLang = Factories.LANG.findByIsoCode(theSettings.get(GmailTwitterHandler.LANGUAGE).toString());
			myForm.setGmailLang(theLang.getId().intValue());
		} else {
			myForm.setLogin(StringShop.EMPTY_STRING);
			myForm.setPassword(StringShop.EMPTY_STRING);
			myForm.setGmailLang(lang.getId().intValue());
		}

		myForm.setLangList(TtsLangData.findAll(user));

		return mapping.getInputForward();
	}

	// Activate the service for a user
	public ActionForward activate(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) {

		final HttpSession session = request.getSession(true);
		final VObject object = SessionTools.getRabbitFromSession(session);
		final Lang lang = SessionTools.getLangFromSession(session, request);
		final MySrvGmailForm myForm = (MySrvGmailForm) form;
		final ActionMessages errors = new ActionMessages();

		final String login = myForm.getLogin();
		final String password = myForm.getPassword();

		try {
			GmailTwitterHandler.createOrUpdateSubscription(null, VObjectData.getData(object), login, password, Factories.LANG.find(myForm.getGmailLang()), true);
		} catch (final Exception e) {
			MySrvGmailAction.LOGGER.fatal(e, e);
			errors.add("scenarioNotCreated", new ActionMessage("errors.addGmail", DicoTools.dico(lang, "srv_podcast/scenario_not_created")));
			saveErrors(request, errors);
			return load(mapping, form, request, response);
		}

		errors.add("registerSucceed", new ActionMessage("errors.addGmail", DicoTools.dico(lang, "srv_podcast/subscription_succeed")));
		saveErrors(request, errors);

		return load(mapping, form, request, response);
	}

	// Update a registred user
	public ActionForward update(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) {

		final HttpSession session = request.getSession(true);
		final VObject object = SessionTools.getRabbitFromSession(session);
		final Lang lang = SessionTools.getLangFromSession(session, request);
		final MySrvGmailForm myForm = (MySrvGmailForm) form;
		final ActionMessages errors = new ActionMessages();

		final String login = myForm.getLogin();
		final String password = myForm.getPassword();

		final List<SubscriptionData> theSubscriptions = SubscriptionData.findByApplicationAndObject(Application.NativeApplication.GMAIL.getApplication(), object);

		if (!theSubscriptions.isEmpty()) {
			try {
				GmailTwitterHandler.createOrUpdateSubscription(theSubscriptions.get(0), VObjectData.getData(object), login, password, Factories.LANG.find(myForm.getGmailLang()), true);
			} catch (final Exception e) {
				MySrvGmailAction.LOGGER.fatal(e, e);
				errors.add("scenarioNotCreated", new ActionMessage("errors.addGmail", DicoTools.dico(lang, "srv_podcast/scenario_not_created")));
				saveErrors(request, errors);
				return load(mapping, form, request, response);
			}
		}

		return load(mapping, form, request, response);
	}

	// Unregistred a user
	public ActionForward delete(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) {
		final HttpSession session = request.getSession(true);
		final VObject object = SessionTools.getRabbitFromSession(session);
		final Lang lang = SessionTools.getLangFromSession(session, request);

		final ActionMessages errors = new ActionMessages();

		for (final SubscriptionData subscription : SubscriptionData.findByApplicationAndObject(Application.NativeApplication.GMAIL.getApplication(), object)) {
			try {
				SubscriptionManager.deleteSubscription(subscription);
			} catch (final Exception e) {
				MySrvGmailAction.LOGGER.fatal(e, e);
			}
		}

		errors.add("registerSucceed", new ActionMessage("errors.deleteRssUser", DicoTools.dico(lang, "srv_podcast/subscription_succeed")));
		saveErrors(request, errors);

		return load(mapping, form, request, response);
	}

}
