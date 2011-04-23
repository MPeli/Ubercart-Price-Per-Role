<?php
// $Id: uc_price_per_role.migrate.inc,v 1.1 2010/02/17 21:55:06 longwave Exp $

/**
 * @file
 * Hooks for handling UberCart Price per role fields on destination nodes.
 */

/**
 * Implements hook_migrate_fields_node().
 */
function uc_price_per_role_migrate_fields_node($type) {
  $enabled = variable_get('uc_price_per_role_enabled', array());
  $fields = array();
  
    foreach (user_roles() as $rid => $role) {
      if ($enabled[$rid]) {
        $fields['role_prices_' . $rid] = t('Purchase price for %role users.', array('%role' => $role));
      }
    }
    
  return $fields;
}

function uc_price_per_role_migrate_prepare_node(&$node, $tblinfo, $row) {
  foreach ($tblinfo->fields as $destfield => $values) {
    if ($values['srcfield'] && isset($row->$values['srcfield'])) {
      $newvalue = $row->$values['srcfield'];
    } 
    else {
      $newvalue = $values['default_value'];
    }
    
    if (drupal_substr($destfield, 0, strlen('role_prices_')) == 'role_prices_') {
      $rid = drupal_substr($destfield, strlen('role_prices_'));
      $node->role_prices[$rid] = $newvalue;
    }
  }

  return $errors;
}