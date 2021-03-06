package net.violet.mynabaztag.action;

import java.util.TimeZone;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import net.violet.mynabaztag.form.MyMessagesSendMp3Form;
import net.violet.mynabaztag.services.ManageMessageServices;
import net.violet.platform.api.exceptions.BlackListedException;
import net.violet.platform.api.exceptions.InternalErrorException;
import net.violet.platform.api.exceptions.ParentalFilterException;
import net.violet.platform.datamodel.Music;
import net.violet.platform.datamodel.User;
import net.violet.platform.datamodel.VObject;
import net.violet.platform.datamodel.factories.Factories;
import net.violet.platform.dataobjects.MessageData.Palette;
import net.violet.platform.struts.ActionWithLog;
import net.violet.platform.util.CCalendar;
import net.violet.platform.util.SessionTools;
import net.violet.platform.util.StringShop;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.upload.FormFile;

public class MyMessagesSendMp3Action extends ActionWithLog {

	@Override
	protected ActionForward doExecute(ActionMapping mapping, ActionForm form, HttpServletRequest request, @SuppressWarnings("unused") HttpServletResponse response) {

		final User user = SessionTools.getUserFromSession(request);

		/**
		 * Check if the user really exists
		 */
		if (user == null) {
			return mapping.findForward("login");
		}

		final MyMessagesSendMp3Form myForm = (MyMessagesSendMp3Form) form;

		final String forward = "messages";
		String message_erreur = "OK";

		// on rcupre mes infos du formulaire
		final int paletteColor = myForm.getColor();
		final Palette palette = Palette.findPaletteByNum(paletteColor);
		final int choixJourDiff = myForm.getChoixJourDiff();
		final int choixMoisDiff = myForm.getChoixMoisDiff();
		final int choixAnneeDiff = myForm.getChoixAnneeDiff();
		final int choixHeureDiff = myForm.getChoixHeureDiff();
		final int choixMinuteDiff = myForm.getChoixMinuteDiff();
		long idMp3 = myForm.getIdMp3();
		final String destName = myForm.getDestName(); // nom du lapin destinataire
		final String sendLater = myForm.getSendLater();
		final String music_name = myForm.getMusicName();
		final FormFile theMusicFile = myForm.getMusicFile();
		final String friendDestName = myForm.getFriendObjectName();

		if (myForm.getSend() == 1) {

			final VObject objectDest = ManageMessageServices.checkDest(friendDestName, destName);

			if (objectDest == null) {
				message_erreur = "no_id_rabbit"; // on a pas r??ussi a r??cup??rer le destinataire
			} else {

				final User userDest = objectDest.getOwner();
				try {
					if (ManageMessageServices.checkSendMessage(user, userDest)) {
						message_erreur = "OK";
					}
				} catch (final ParentalFilterException e) {
					message_erreur = "parental_error";
				} catch (final BlackListedException e) {
					message_erreur = "black_list_error";
				}

				// on regarde s'il s'agit d'un envoi diff??r??
				boolean envoiDiff = false;
				if (sendLater.equals("send_later")) {
					envoiDiff = true;
				}

				if (message_erreur.equals("OK")) {
					if (idMp3 <= 0) {
						idMp3 = MyManageMp3Action.createMP3(music_name, theMusicFile, user, 0);
					}
				}
				// recup??re l'id de la liste des mp3 ou du upload de mp3
				final Music theMusic = Factories.MUSIC.find(idMp3);

				if (theMusic == null) {
					message_erreur = "server_error"; // probl??me le mp3 n'existe pas
				} else {

					if (message_erreur.equals("OK")) {
						CCalendar theDeliveryDate = null;
						if (envoiDiff) { // message envoi diff??r?? constuction du nexttime
							final String time_zone = user.getTimezone().getTimezone_javaId();
							final TimeZone tz = TimeZone.getTimeZone(time_zone);

							theDeliveryDate = new CCalendar(tz);
							theDeliveryDate.set(choixAnneeDiff, choixMoisDiff - 1, choixJourDiff, choixHeureDiff, choixMinuteDiff);
						}
						try {
							ManageMessageServices.sendUserMessageAndNotification(user, objectDest, theMusic.getFile(), theDeliveryDate, palette, theMusic.getMusic_name());
						} catch (final InternalErrorException e) {
							message_erreur = "server_error";
						}
					}
				}
			}
		} else { // ecoute du mp3 perso
			final Music theMusic = Factories.MUSIC.find(idMp3);
			String url = StringShop.EMPTY_STRING;
			if ((theMusic != null) && (theMusic.getFile() != null)) {
				url = theMusic.getFile().getPath();
			}

			myForm.setUrl(url);
			return mapping.findForward("playIt");
		}
		myForm.setErreur(message_erreur);
		return mapping.findForward(forward);
	}
}
