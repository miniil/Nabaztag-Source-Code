package net.violet.platform.datamodel;

import java.sql.Timestamp;

import net.violet.db.records.Record;

public interface Notification extends Record<Notification> {

	/**
	 * Notification Status
	 */
	public static enum NOTIFICATION_STATUS {
		PENDING, REJECTED, ACCEPTED, FINISHED, CANCELLED
	};

	VObject getSender();

	VObject getRecipient();

	Application getApplication();

	Timestamp getNotificationDate();

	String getStatus();
}
