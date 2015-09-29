<?php
/**
 * @file
 *   Expose the devshop_varnish feature to hostmaster.
 */

/**
 * Implementation of hook_hosting_feature().
 */
function devshop_varnish_hosting_feature() {
    $features['devshop_varnish'] = array(
        'title' => t('Apache + Varnish Web Server'),
        'description' => t('Allows Varnish + Apache web servers.'),
        'module' => 'devshop_varnish',
    );
    return $features;
}

