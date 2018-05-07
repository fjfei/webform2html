<?php
function theme_webform2html_content($vars) {
  return webform_replace_tokens($vars['template']['hs_body']['value'], $vars['node'], $vars['submission'], array(''), TRUE);
} // function theme_webform2html_content()