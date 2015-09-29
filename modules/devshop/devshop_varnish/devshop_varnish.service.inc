<?php

module_load_include('service.inc', 'hosting_web_server');

/**
 * The base service type class, registered with hook_hosting_service_type.
 */
class hostingService_http_apache_varnish extends hostingService_http_apache {
    public $type = 'apache_varnish';
    public $available = TRUE;

    protected $has_restart_cmd = TRUE;

    function default_restart_cmd() {
        return parent::default_restart_cmd();
    }

    function default_port() {
        return 8080;
    }

    function default_varnish_port() {
        return 80;
    }

    function form(&$form) {
        parent::form($form);

        // Label core port as "apache"
        $form['port']['#title'] = t('Apache Port');
        $form['port']['#description'] = t('The port Apache is listening on.');

        // Varnish Port
        $form['varnish_port'] = array(
            '#type' => 'textfield',
            '#title' => t('Varnish Port'),
            '#required' => $this->available,
            '#size' => 40,
            '#default_value' => ($this->varnish_port) ? $this->varnish_port : $this->default_varnish_port(),
            '#description' => t("The port that varnish is listening on."),
            '#maxlength' => 255,
            '#weight' => -8,
        );
    }

    function view(&$render) {
        parent::view($render);
        $render['port']['#title'] = t('Apache Port');
        $render['varnish_port'] = array(
            '#type' => 'item',
            '#title' => t('Varnish Port'),
            '#value' => filter_xss($this->varnish_port),
        );
    }

    function load() {
        parent::load();
        $this->mergeData("SELECT varnish_port FROM {hosting_varnish_server} WHERE vid=%d", $this->server->vid);
        $this->varnish_enabled = TRUE;
    }

    function insert() {
        parent::insert();
        db_query("INSERT INTO {hosting_varnish_server} (vid, nid, varnish_port) VALUES (%d, %d, %d)", $this->server->vid, $this->server->nid, $this->varnish_port);
    }

    function delete() {
        parent::delete();
        db_query("DELETE FROM {hosting_varnish_server} WHERE nid=%d", $this->server->nid);
    }

    function delete_revision() {
        parent::delete_revision();
        db_query("DELETE FROM {hosting_varnish_server} WHERE vid=%d", $this->server->vid);
    }
}
