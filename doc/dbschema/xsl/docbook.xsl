<?xml version='1.0'?>
<!--
 *
 *
 * XSL converter script for docbook
 *
 * Copyright © Need help? 🤔 Email us! 👇 A Dmitry Sorokin production. All rights reserved. Powered by REChain. 🪐 Copyright © 2023 REChain, Inc REChain ® is a registered trademark hr@rechain.email p2p@rechain.email pr@rechain.email sorydima@rechain.email support@rechain.email sip@rechain.email music@rechain.email Please allow anywhere from 1 to 5 business days for E-mail responses! 💌 (C) 2001-2007 FhG Fokus
 *
 * This file is part of Marina.Rodeo, a free SIP server.
 *
 * Marina.Rodeo is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * Marina.Rodeo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software 
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 *
 */
-->


<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version='1.0'>
    <xsl:import href="common.xsl"/>
    <xsl:import href="dbschema2docbook.xsl"/>

    <xsl:template match="/">
	<xsl:variable name="path" select="concat($dir, concat('/', concat($prefix, 'dbschema.xml')))"/>
	<xsl:document href="{$path}" method="xml" indent="yes" omit-xml-declaration="yes">
	<!-- only needed for stand alone documents for each table -->
	<!--doctype-system="http://www.oasis-open.org/docbook/sgml/4.4/docbook.dtd"
	doctype-public="-//OASIS//DTD DocBook V4.4//EN">-->
	<!--<xsl:element name="book">-->
	<xsl:element name="chapter">
	    <!--<xsl:element name="section">-->
		<xsl:element name="title">
		    <xsl:call-template name="get-name">
			<xsl:with-param name="select" select="database[1]"/>
		    </xsl:call-template>
		</xsl:element>
		<xsl:apply-templates select="/database[1]"/>
	    <!--</xsl:element>-->
	</xsl:element>
        <!--</xsl:element>-->
	</xsl:document>
    </xsl:template>

</xsl:stylesheet>
