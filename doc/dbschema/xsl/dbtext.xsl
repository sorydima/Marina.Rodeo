<?xml version='1.0'?>
<!--
 *
 *
 * XSL converter script for dbtext
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
                xmlns:xi="http://www.w3.org/2001/XInclude">

    <xsl:import href="common.xsl"/>
    <xsl:output method="text" indent="no" omit-xml-declaration="yes"/>

    <!-- Create the file for the table in dbtext subdirectory -->
    <xsl:template match="table">
	<xsl:variable name="name">
	    <xsl:call-template name="get-name"/>
	</xsl:variable>
	
	<xsl:variable name="path" select="concat($dir, concat('/', concat($prefix, $name)))"/>
	<xsl:document href="{$path}" method="text" indent="no" omit-xml-declaration="yes">
		<xsl:apply-imports/>
		<!-- Insert version data -->
		 <xsl:apply-templates select="version"/> 
		<!-- this is not exactly what we want for dbtext, as the version data gets
		     appended to the actual table file, and no to the 'version' table.
		     But its not possible (at least with XSL 1.0, AFAIK) to append data to a
		     file. So it's much more easier to do this in the Makefile -->
	</xsl:document>
    </xsl:template>

    <!-- version data template -->
    <xsl:template match="version">
	<xsl:call-template name="get-name">
	    <xsl:with-param name="select" select="parent::table"/>
	</xsl:call-template>
	<xsl:text>:</xsl:text>
	<xsl:value-of select="text()"/>
	<xsl:text>&#x0A;</xsl:text>
    </xsl:template>

    <!-- Create column definitions -->
    <xsl:template match="column">
	<xsl:variable name="type">
	    <xsl:call-template name="get-type"/>
	</xsl:variable>

	<xsl:variable name="null">
	    <xsl:call-template name="get-null"/>
	</xsl:variable>

	<xsl:call-template name="get-name"/>
	<xsl:text>(</xsl:text>
	<xsl:choose>
	    <xsl:when test="type[@db=$db]">
		<xsl:value-of select="normalize-space(type[@db=$db])"/>
	    </xsl:when>
	    <xsl:when test="$type='char' or 
						$type='short' or 
						$type='int' or
						$type='long' or 
						$type='datetime'">
		<xsl:text>int</xsl:text>
	    </xsl:when>
	    <xsl:when test="$type='float' or 
						$type='double'">
		<xsl:text>double</xsl:text>
	    </xsl:when>
	    <xsl:when test="$type='string' or
						$type='text'">
		<xsl:text>string</xsl:text>
	    </xsl:when>
		<xsl:when test="$type='binary'">
		<xsl:text>blob</xsl:text>
	    </xsl:when>
	    <xsl:otherwise>
		<xsl:call-template name="type-error"/>
	    </xsl:otherwise>
	</xsl:choose>

	<xsl:if test="$null=1">
	    <xsl:text>,null</xsl:text>
	</xsl:if>
	<xsl:text>) </xsl:text>
	<xsl:if test="position()=last()">
	    <xsl:text>&#x0A;</xsl:text>
	</xsl:if>
    </xsl:template>

    <!-- Escape all : occurrences -->
    <xsl:template name="escape">
	<xsl:param name="value"/>
	<xsl:choose>
	    <xsl:when test="contains($value, ':')">
		<xsl:value-of select="concat(substring-before($value, ':'), '\:')"/>
		<xsl:call-template name="escape">
		    <xsl:with-param name="value" select="substring-after($value, ':')"/>
		</xsl:call-template>
	    </xsl:when>
	    <xsl:otherwise>
		<xsl:value-of select="$value"/>
	    </xsl:otherwise>
	</xsl:choose>
    </xsl:template>

</xsl:stylesheet>
