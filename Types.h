/* $Id: Types.h 3988 2015-08-17 15:55:34Z tranvan $ */
#ifndef DBTOOLS_TYPES_H
#define DBTOOLS_TYPES_H

/**************************************************************************//**
 *	\file	DbTools/Types.h
 *	\brief	DBMS Basic types definition
 *
 *	\author Kevin JACQUEMIN (KJ)
 *	\date 23-04-2008
 *	\version 1.0
 *****************************************************************************/

#undef IN
#undef OUT

// For Hardware failure simulator comment the line to disable it
#if defined(XS) && XS
#define WITH_FAILUREPOINTS
#define WITH_TEARINGPOINTS

#define WITH_DBIO
#define WITH_DBQ
#endif /* XS */

/**************************************************************************//**
 * \defgroup dbtools    DBMS utility functions and definitions
 *****************************************************************************/
/*@{*/
/*@}*/

/**************************************************************************//**
 * \defgroup dbtools_types    Various data type definitions
 * \ingroup dbtools
 * \details Types used by Gemalto on the SmartCard
 *			Basic types size are architecture dependant, so this file is also.
 *****************************************************************************/
/*@{*/

/* alias stdint.h types */
#if !(defined(XS) && XS)

#ifdef _MSC_VER
#include <ms_stdint.h>
#else
//#ifdef __CYGWIN__
#include <stdint.h>
//#endif /* __CYGWIN__ */
#endif /* _MSC_VER */

#define BYTES_PER_SECTOR	512

/* TODO: maybe use stdint.h types everywhere ?
	LwIP/port/STM32F2x7/arch/cc.h already has these types: */
#ifndef __CC_H__
typedef uint8_t			u8_t;
typedef int8_t			s8_t;
typedef uint16_t		u16_t;
typedef int16_t			s16_t;
typedef uint32_t		u32_t;
typedef int32_t			s32_t;
#endif /* __CC_H__ */

#else /* XS */

typedef uint8			u8_t;
typedef uint16			u16_t;
typedef uint32			u32_t;
typedef int8			s8_t;
typedef int16			s16_t;
typedef int32			s32_t;

typedef int32			intptr_t;

#endif /* XS */

/* remove volatile flag from variables for non-ARM targets */
#ifndef __arm__
#define __IO
#endif /* __arm__ */

/*=============================================================================
	Prototype Types

	Definition of some specific structures for our protoype
=============================================================================*/

/**************************************************************************//**
 * offset in the parameters array
 */
typedef		u16_t	in_param;
/**************************************************************************//**
 * Operator's result header index in RESULT_headers array
 */
typedef		u8_t	out_result;

/**************************************************************************//**
 * definition of a date in DBMS
 */
typedef struct _date_t
{
	u8_t day;	/**< day (from 1 to 31) */
	u8_t month;	/**< month (from 1 to 12) */
	u16_t year;	/**< year expressed with four digits */
} date_t;

/* make fake bitfield names to make ARM compiler happy */
#ifdef __arm__
#define FAKE_BITFIELD _fake_bitfield
#else
#define FAKE_BITFIELD
#endif /* __arm__ */

/***************************************************************************//**
 * \brief Generic NAND address
 *
 * It conveniently combines different types of NAND addresses, in particular:
 * - absolute number of:
 * -- [sectors]			sectors (0-2^32)
 * -- [pages.num]		pages (0-2^30) (i.e. 0-1073741823)
 * -- [blocks.num]		blocks (0-2^24) (i.e. 0-16777215)
 * - decomposition of address into number of:
 * -- [addr.sector]		sectors in page (0-3)
 * -- [addr.page]		pages in block (0-63)
 * -- [addr.block]		blocks (0-2^24) (i.e. 0-16777215)
 *
 * This data type size is 4 bytes
 */
typedef union _nand_addr
{
	uint32_t			sectors;
	struct _nand_pages
	{
		unsigned int FAKE_BITFIELD	: 2; /* sector */
		unsigned int	num			:30;
	} pages;
	struct _nand_blocks
	{
		unsigned int FAKE_BITFIELD	: 8; /* sector + page */
		unsigned int	num			:24;
	} blocks;
	struct _addr
	{
		unsigned int	sector		: 2;
		unsigned int	page		: 6;
		unsigned int	block		:24;
	} addr;
} NAND_Addr, *PNAND_Addr, FTL_Addr, *PFTL_Addr;

/**************************************************************************//**
 * \brief Generic NOR address
 *
 * Incorporates two addressing methods:
 * - [ptr]				absolute offset to the specific byte in NOR (0-2^32)
 * - [block]			per-block addressing:
 * -- [blocks.offset]	offset to the specific byte within NOR block (0-255)
 * -- [blocks.num]		NOR block number (0-2^24) (i.e. 0-16777215)
 *
 * This data type size is 4 bytes
 */
typedef union _nor_addr
{
	uint32_t			ptr;
	struct _nor_blocks
	{
		unsigned int	offset	: 8;
		unsigned int	num		:24;
	} blocks;
} NOR_Addr, *PNOR_Addr;

typedef union _norng_addr
{
	uint32_t			ptr;
	struct _norng_blocks
	{
		unsigned int	offset	:17;
		unsigned int	num		:15;
	} blocks;
	struct _norog_blocks
	{
		unsigned int	offset	: 8;
		unsigned int	num		:24;
	} og_blocks;
} NORng_Addr, *PNORng_Addr;


typedef u8_t SWS_Id;

/***************************************************************************//**
 * \brief Backup/Recovery structure for SWS NAND sectors
 *
 * It combines:
 * - the NAND address of the sector
 * - the ID of the SWS this sector belongs to
 * - the content of the sector
 *
 * This data type size is 516 bytes
 */
typedef struct _recovery_NAND_sector_desc
{
	NAND_Addr sector_addr;												/**< NAND address of the sector to backup / restore */
	u8_t sector_content[ BYTES_PER_SECTOR ];			/**< Content of the sector */
	SWS_Id sws_id;																/**< ID of the SWS */
} recovery_NAND_sector_desc;

/*@}*/
/**************************************************************************//**
 * \defgroup dbtools_types_op  Operator routines and types
 * \ingroup dbtools_types
 *****************************************************************************/
/*@{*/

/**************************************************************************//**
 * \brief Operator call types
 */
typedef enum _OpCallType
{
	OP_CALL_OPEN,	/* = 100 */
	OP_CALL_NEXT,	/* = 101 */
	OP_CALL_CLOSE
} OpCallType;

/**************************************************************************//**
 * \brief Operator status code
 */
typedef enum _OpStatus
{
	OP_STATUS_DEFAULT		,	// = 0
	OP_STATUS_CALL_CHILD	,	// = 1
	OP_STATUS_OPEN_DONE		,	// = 2
	OP_STATUS_INSERT_DONE	,	// = 3
	OP_STATUS_TUPLE_PRODUCED,	// = 4
	OP_STATUS_TUPLE_CONSUMED,	// = 5
	OP_STATUS_END_OF_FILE	,	// = 6
	OP_STATUS_CLOSE_DONE	,	// = 7
	OP_STATUS_TUPLE_DELETED	,	// = 8
	OP_STATUS_REOPEN		,	// = 9
	OP_STATUS_TUPLE_SKIP	,	// = 10
	OP_STATUS_UNDEFINED = (u8_t)-1
} OPStatus;

/**************************************************************************//**
 * \brief Operator structure declaration
 *
 *  Operator functions first parameter is an id of the operator being processed.
 *  They return error code.
 */
struct _OP;
typedef struct _OP
{
	u8_t	id;		/**< operator id */
	u8_t	child1;	/**< id of left child operator (or ILLEGAL_OP_ID) */
	u8_t	child2;	/**< id of right child operator (or ILLEGAL_OP_ID) */
	u8_t	father;	/**< parent operator id (or ILLEGAL_OP_ID) */
	OPStatus status;/**< operator status */

	OPStatus (*open )( struct _OP* operation );	/**< open() operator function pointer */
	OPStatus (*next )( struct _OP* operation );	/**< next() operator function pointer */
	OPStatus (*close)( struct _OP* operation );	/**< close() operator function pointer */

	in_param	IN;	/**< offset in the parameters array */
	out_result	OUT;/**< offset in the result array */
} OP;

/*@}*/
/**************************************************************************//**
 * \defgroup dbtools_types_meta  Data types for metadata management
 * \ingroup dbtools_types
 *****************************************************************************/
/*@{*/

/////////////////////////////
//
// upper bounds of meta data

#define MAX_TAB_NUM 15
#define MAX_TAB_COL 110
#define MAX_FK_NUM  11
#define MAX_SKT_NUM 6
#define MAX_SKT_COL 20
#define MAX_CI_NUM  11

#define MAX_COLNAME_SIZE 20
#define MAX_TABNAME_SIZE 15
#define MAX_SKTNAME_SIZE 15

#define MAX_BF_HASH_FUNC_NUM 7

/**************************************************************************//**
 * Table descriptor
 */
typedef struct _tab_desc
{
	u16_t	tuple_size;		/**< tuple size */
	u8_t	tab_id;			/**< identifier of the table */
	SWS_Id	sws_id;			/**< SWS identifier */
	u8_t	tab_name[ MAX_TABNAME_SIZE ];	/**< table name */
} tab_desc;

/**************************************************************************//**
 * Column descriptor
 */
typedef struct _col_desc
{
	u8_t	tab_id;
	u8_t	type;		/** column data type (i.e. DataType) */
	u16_t	col_id;
	u16_t	size;
	u16_t	offset;
	u8_t	col_name[ MAX_COLNAME_SIZE ];
} tab_col_desc;

/**************************************************************************//**
 * Foreign Key descriptor
 */
typedef struct _fk_desc
{
	u8_t	tab_id;
	u8_t	ref_tab_id;
	u16_t	col_id;
	u16_t	ref_col_id;
} fk_desc;

/**************************************************************************//**
 * SKT (Subtree Key Table) descriptor
 */
typedef struct _skt_desc
{
	u16_t	tuple_size;
	u8_t	skt_id;
	u8_t	tab_id;
	SWS_Id	sws_id;
#ifdef WITH_TRACES
	u8_t	skt_name[ MAX_SKTNAME_SIZE ];
#endif /* WITH_TRACES */
} skt_desc;

/**************************************************************************//**
 * SKT column descriptor
 */
typedef struct _skt_col_desc
{
	u16_t	offset;
	u16_t	ref_col_id;
	u8_t	skt_id;
	u8_t	ref_tab_id;
	u8_t	IsChild;	/**< is 1 if column is one level lower than
							SKT primary key, otherwise zero */
} skt_col_desc;

/**************************************************************************//**
 * Climbing Indexes (PTRs + KAs + SKAs)
 */
typedef struct _ka_desc
{
	u8_t	ka_id;
	u8_t	tuple_type;		/**< integer, string, etc.? FIXME enum */
	u16_t	tuple_size;		/**< related to the entry type? */
	u8_t	ref_table_id;	/**< table the KA is attached to */
	u8_t	table_id;		/**< table the KA indexes */
	u16_t	col_id;			/**< indexed attribute of the indexed table */
	u8_t	unique;			/**< whether it contains only unique tuples (primary index) */
	u8_t	ska_id;			/**< associated SKA */
	u8_t	ptr_id;			/**< associated PTR */
	SWS_Id	sws_id;			/**< SWS identifier */
} ka_desc;

typedef struct _ska_desc
{
	u8_t	ska_id;
	u8_t	size_per_key;	/**< byte count per key (i.e. m/n/8 in BFs' formulas) */
	u8_t	num_funcs;		/**< number of hash functions used by the BF */
	u8_t	scan_limit;		/**< number of sectors to read before giving up (used in PTR) */
	u8_t	ref_ka_id;		/**< KA summarized by this SKA */
	SWS_Id	sws_id;			/**< SWS identifier */
} ska_desc;

typedef struct _ptr_desc
{
	u16_t	tuple_size;		/**< size of the pointers */
	u8_t	ptr_id;
	u8_t	ref_ka_id;		/**< KA the PTR is attached to */
	SWS_Id	sws_id;			/**< SWS identifier */
} ptr_desc;

/**************************************************************************//**
 * meta data summary (number of each structure created)
 */
typedef struct _meta_summary
{
	u16_t	tab_col;/**< number of columns */
	u8_t	tab;	/**< number of tables */
	u8_t	fk;		/**< number of foreign keys */
	u8_t	skt;	/**< number of SKT */
	u8_t	skt_col;/**< number of SKT columns */
	u8_t	ptr;	/**< number of PTR */
	u8_t	ka;		/**< number of KA */
	u8_t	ska;	/**< number of SKA */
} meta_summary;

/*@}*/
#endif /* DBTOOLS_TYPES_H */
