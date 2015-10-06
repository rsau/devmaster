<?php

/**
 * Implements hook_hosting_server_context_options
 * @param $task
 */
function devshop_varnish_hosting_server_context_options(&$task) {
    $node = $task->ref;

    drush_log(print_r($node, 1), 'ok');

    if (isset($node->services['http']->varnish_enabled)) {
        drush_log('VARNISH ENABLED!', 'warning');
        // we pass null to disable the option.
        $task->context_options['varnish_enabled'] = TRUE;
        $task->context_options['varnish_port'] = $node->services['http']->varnish_port;
    }
    else {
        drush_log('$node->services[http]->varnish_enabled is FALSE', 'warning');

    }
}