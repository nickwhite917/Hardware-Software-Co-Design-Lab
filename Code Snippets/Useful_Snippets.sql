--Script header
/*
  ==============================================================================
  Purpose:  Build and execute a dynamic select query based on specified parameters.  Include
            only records that meet all filtering criteria.  Empty criteria are ignored.
  Accepts:  @ModeCode          Indicates result set: C=count, D=display E=empty, 
                                 K=kanban, M=mass edit search, U=update for mass edit.
            @ColumnSetId       Identifies the set of FieldIds that define the columns
                                 of the return data set.
            @DivisionId        Identifies the division.
            @LocationIds       List of LocationIds separated by commas.
            @PartStatus        Status of part: 0=Inactive, 1=Active, 2=All
            @PeriodId          Identifies the period for time based fields.
            @PeriodRange       Identifies the range for statistical data.
            @FilterId          Identifies an applied saved filter.
            @MaxRowsPerPage    Maximum number of rows to return. Use NULL for all records (unpaged).
            @StartRowIndex     Row number of first row returned from full result set.
            @FilterExpression  Lists additional display grid filter criteria.
            @ExtraExpression   Lists display grid sort criteria or new field value (Update mode).
  Calls:    None.
  Returns:  Rows selected by the query generated.
  Note:     This procedure must be updated for table additions/removals in the database.
            The table of each field that is set displayable must be included 
            in this procedure for these fields to display in the grid.
  History:
  06/21/15 DRL 245019 Complete rewrite
  ==============================================================================
  */

  /*
  ==============================================================================
  Purpose:  Create the EMPLOYEE table. 
  Columns:  
  Calls:    None.
  Returns:  Print statements.
  Note:     
  History:
  09/15/15 NJW Lab1 Initial version
  ==============================================================================
*/

IF OBJECT_ID (N'mytablename', N'U') IS NULL

-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- ** NOTE **
-- This script is not executable! See description for details on how to
-- use this script.
--
-- ** DESCRIPTION **
--  This file contains many useful query templates and code snippets
--  for use in MS SQL Management Studio. All code created by Nick White
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

-- Script Header (Details what is going to happen in the script)
-- /////////////////////////////////////////////////////////////////////////////
PRINT N'';
PRINT N'Script    Objective:	Create New Table';
PRINT N'Script  Information:	Run against LogilityPHAdmin Database';
PRINT N'Tables	   Effected:	1';
PRINT N'				  1)	[dbo.BatchLog]';
PRINT N'';
-- /////////////////////////////////////////////////////////////////////////////	

-- Debug Section (Prints output to console if reached. Put before and after script section. )
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
PRINT N'';
PRINT N'Create [dbo].[EMPLOYEE] Table -- Begin | OPERATION 1 of 2';
PRINT N'';
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
PRINT N'';
PRINT N'Create [dbo].[EMPLOYEE] Table -- End | OPERATION 2 of 2';
PRINT N'';
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- More to come soon