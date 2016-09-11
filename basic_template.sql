
/*
CREATE TABLE TEST (
pk_test INT,
fk_other INT,
localname VARCHAR(400),
localnumber INT,
CONSTRAINT pk_test PRIMARY KEY (pk_test),
CONSTRAINT fk_other FOREIGN KEY (fk_other) REFERENCES OTHER
);
*/

CREATE TABLE INVESTORS (
pk_investor INT,

/* name */
/* email */
/* description */
/* date of inclusion */

CONSTRAINT pk_investors PRIMARY KEY (pk_investors)
);

CREATE TABLE SUBJECTS (
pk_subject INT,

/* tag (project, subproject, task type, whatever) */
/* description */
/* date of inclusion */

CONSTRAINT pk_subjects PRIMARY KEY (pk_subjects)
);

CREATE TABLE CURRENCIES (
pk_currency INT,

/* label */
/* description */
/* date of inclusion */

CONSTRAINT pk_currencies PRIMARY KEY (pk_currencies)
);

CREATE TABLE INVESTED_TIME (
pk_invested_time INT,

/* investor (fk -> investors.pk_investor) */
/* date */
/* description */
/* comment (optional) */
/* subject (fk -> subjects.pk_subject) */
/* minutes */
/* price per unit */
/* currency type (fk -> currencies.pk_currency) */

CONSTRAINT pk_invested_time PRIMARY KEY (pk_invested_time)
);

CREATE TABLE INVESTED_ASSET (
pk_invested_asset INT,

/* investor (fk -> investors.pk_investor) */
/* date */
/* short_name */
/* description */
/* comment (optional) */
/* subject (fk -> subjects.pk_subject) */
/* price */
/* currency type (fk -> currencies.pk_currency) */

CONSTRAINT pk_invested_asset PRIMARY KEY (pk_invested_asset)
);

CREATE TABLE BONUSES (
pk_bonus INT,

/* investor (fk -> investors.pk_investor) */
/* date */
/* short_name */
/* description */
/* comment (optional) */
/* subject (fk -> subjects.pk_subject) */
/* reward */

CONSTRAINT pk_bonuses PRIMARY KEY (pk_bonuses)
);

CREATE TABLE INVESTED_MONEY (
pk_invested_money INT,

/* investor (fk -> investors.pk_investor) */
/* date */
/* short_name */
/* description */
/* comment (optional) */
/* subject (fk -> subjects.pk_subject) */
/* amount */
/* currency type (fk -> currencies.pk_currency) */

CONSTRAINT pk_invested_money PRIMARY KEY (pk_invested_money)
);

