<?xml version='1.0'?>
<!--
 *
 *
 * XSL converter script for postgresql databases
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


<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version='1.0'
                xmlns:xi="http://www.w3.org/2001/XInclude"
>

    <xsl:import href="sql.xsl"/>

<!-- specify the table type -->
    <xsl:template name="table.close">
	<xsl:text>)</xsl:text>
	<xsl:if test="type[@db=$db]">
	    <xsl:text> Type=</xsl:text>
	    <xsl:value-of select="normalize-space(type[@db=$db])"/>
	</xsl:if>
	<xsl:text>;&#x0A;&#x0A;</xsl:text>
	<xsl:for-each select="column">
	    <xsl:if test="autoincrement">
	        <xsl:call-template name="alter_sequence"/>
	    </xsl:if>
	</xsl:for-each>
    </xsl:template>

    <xsl:template name="column.type">
	<xsl:variable name="type">
	    <xsl:call-template name="get-type"/>
	</xsl:variable>

	<xsl:choose>
	    <xsl:when test="type[@db=$db]">
		<xsl:value-of select="normalize-space(type[@db=$db])"/>
	    </xsl:when>
		<!--transform bigint primary key autoincrement to BIGSERIAL PRIMARY KEY -->
		<xsl:when test="$type='long' and autoincrement and primary">
		    <xsl:text>BIGSERIAL PRIMARY KEY</xsl:text>
		</xsl:when>
		<!--transform bigint autoincrement to BIGSERIAL -->
		<xsl:when test="$type='long' and autoincrement">
		    <xsl:text>BIGSERIAL</xsl:text>
		</xsl:when>
	    <xsl:when test="$type='char'">
		<xsl:text>SMALLINT</xsl:text>
		<xsl:call-template name="column.trailing"/>
	    </xsl:when>
	    <xsl:when test="$type='short'">
		<xsl:text>SMALLINT</xsl:text>
		<xsl:call-template name="column.trailing"/>
	    </xsl:when>
	    <xsl:when test="$type='int'">
			<xsl:if test="not(autoincrement)">
				<xsl:text>INTEGER</xsl:text>
			</xsl:if>
		<xsl:call-template name="column.trailing"/>
	    </xsl:when>
	    <xsl:when test="$type='long'">
		<xsl:text>BIGINT</xsl:text>
		<xsl:call-template name="column.trailing"/>
	    </xsl:when>
	    <xsl:when test="$type='datetime'">
		<xsl:text>TIMESTAMP</xsl:text>
		<xsl:call-template name="column.trailing"/>
	    </xsl:when>
	    <xsl:when test="$type='double'">
		<xsl:text>DOUBLE PRECISION</xsl:text>
		<xsl:call-template name="column.trailing"/>
	    </xsl:when>
	    <xsl:when test="$type='float'">
		<xsl:text>REAL</xsl:text>
		<xsl:call-template name="column.trailing"/>
	    </xsl:when>
	    <xsl:when test="$type='string'">
		<xsl:text>VARCHAR</xsl:text>
		<xsl:call-template name="column.size"/>
		<xsl:call-template name="column.trailing"/>
	    </xsl:when>
	    <xsl:when test="$type='binary'">
		<xsl:text>BYTEA</xsl:text>
		<xsl:call-template name="column.trailing"/>
	    </xsl:when>
	    <xsl:when test="$type='text'">
		<xsl:text>TEXT</xsl:text>
	    </xsl:when>
	    <xsl:otherwise>
		<xsl:call-template name="type-error"/>
	    </xsl:otherwise>
	</xsl:choose>
	</xsl:template>

	<xsl:template name="column.trailing">
	<xsl:variable name="column.type">
	    <xsl:call-template name="get-type"/>
	</xsl:variable>
	<xsl:if test="$column.type='datetime'">
	    <xsl:text> WITHOUT TIME ZONE</xsl:text>
	</xsl:if>
	<xsl:if test="autoincrement">
		<xsl:text>SERIAL</xsl:text>
	</xsl:if>
	<!-- PRIMARY KEY column definition -->
	<xsl:if test="primary">
		<xsl:text> PRIMARY KEY</xsl:text>
	</xsl:if>
	</xsl:template>

	<xsl:template name="get-index-name">
	<xsl:variable name="index.name">
	    <xsl:call-template name="get-name"/>
	</xsl:variable>
	<xsl:variable name="table.name">
	    <xsl:call-template name="get-name">
		<xsl:with-param name="select" select="parent::table"/>
	    </xsl:call-template>
	</xsl:variable>
	<!-- because postgres don't like identical index names, even on table level -->
	<xsl:value-of select="concat($table.name, '_', $index.name)"/>
	</xsl:template>

<!-- ################ SEQUENCE (alter) ################  -->
<!-- ALTER SEQUENCE location_id_seq MAXVALUE 2147483647 CYCLE; -->
	<xsl:template name="alter_sequence">
	    <xsl:variable name="table.name">
		<xsl:call-template name="get-name">
		    <xsl:with-param name="select" select="parent::table"/>
		</xsl:call-template>
	    </xsl:variable>
	    <xsl:variable name="column.name">
		<xsl:call-template name="get-name"/>
	    </xsl:variable>

	    <xsl:text>ALTER SEQUENCE </xsl:text>
	    <xsl:value-of select="$table.name"/>
	    <xsl:text>_</xsl:text>
	    <xsl:value-of select="$column.name"/>
	    <xsl:text>_seq MAXVALUE 2147483647 CYCLE;&#x0A;</xsl:text>
	</xsl:template>
<!-- ################ /SEQUENCE (alter) ################  -->

</xsl:stylesheet>
