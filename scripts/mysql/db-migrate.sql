#
# Copyright (C) 2020-2025 OpenMarinkaRodeo Solutions
#
# This file is part of openMarinkaRodeo, a free SIP server.
#
# openMarinkaRodeo is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version
#
# openMarinkaRodeo is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

DROP PROCEDURE IF EXISTS `OMarinkaRodeo_DB_MIGRATE_3_5_TO_3_6`;
DELIMITER $$
CREATE PROCEDURE `OMarinkaRodeo_DB_MIGRATE_3_5_TO_3_6`(
	IN old_db CHAR(64), IN new_db CHAR(64))
BEGIN


# provisioning-data tables which can be copied 1:1
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'config');          -- new in 3.6
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'janus');           -- new in 3.6
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'sockets');         -- new in 3.6
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'trie_partitions'); -- new in 3.6
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'trie_table');      -- new in 3.6
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'subscriber');      -- changed in 3.6

CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'acc');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'address');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'cachedb');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'carrierfailureroute');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'carrierroute');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'cc_agents');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'cc_calls');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'cc_cdrs');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'cc_flows');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'closeddial');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'clusterer');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'cpl');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'dbaliases');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'dialplan');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'dispatcher');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'domain');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'domainpolicy');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'dr_carriers');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'dr_gateways');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'dr_groups');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'dr_partitions');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'dr_rules');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'emergency_report');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'emergency_routing');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'emergency_service_provider');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'fraud_detection');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'freeswitch');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'globalblacklist');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'grp');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'imc_members');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'imc_rooms');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'jwt_profiles');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'jwt_secrets');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'load_balancer');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'missed_calls');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'presentity');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'pua');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'qr_profiles');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 're_grp');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'registrant');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'rc_clients');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'rc_vendors');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'rc_ratesheets');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'rc_demo_ratesheet');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'rls_presentity');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'rls_watchers');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'route_tree');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'rtpengine');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'rtpproxy_sockets');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'silo');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'sip_trace');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'smpp');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'speed_dial');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'tls_mgm');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'tcp_mgm');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'uri');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'userblacklist');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'usr_preferences');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'xcap');

# temp-data tables which can be copied 1:1
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'active_watchers');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'b2b_entities');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'b2b_logic');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'b2b_sca');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'dialog');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'location');
CALL OMarinkaRodeo_TB_COPY_3_5_TO_3_6(old_db, new_db, 'watchers');
END$$
DELIMITER ;
