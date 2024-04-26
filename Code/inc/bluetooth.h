#ifndef BT
#define BT

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/services/bas.h>
#include <zephyr/bluetooth/services/hrs.h>

extern struct bt_conn_auth_cb auth_cb_display;

void connected(struct bt_conn *conn, uint8_t err);
void disconnected(struct bt_conn *conn, uint8_t reason);
void bt_ready(void);
void auth_cancel(struct bt_conn *conn);
void bas_notify(void);
void hrs_notify(void);

#endif