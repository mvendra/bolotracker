
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
fk_investor INT,
fk_subject INT,
fk_currency INT,

/* date */
/* description */
/* comment (optional) */
/* minutes */
/* price per unit */

CONSTRAINT pk_invested_time PRIMARY KEY (pk_invested_time),
CONSTRAINT fk_investor FOREIGN KEY (fk_investor) REFERENCES INVESTORS,
CONSTRAINT fk_subject FOREIGN KEY (fk_subject) REFERENCES SUBJECTS,
CONSTRAINT fk_currency FOREIGN KEY (fk_currency) REFERENCES CURRENCIES
);

CREATE TABLE INVESTED_ASSET (
pk_invested_asset INT,
fk_investor INT,
fk_subject INT,
fk_currency INT,

/* date */
/* short_name */
/* description */
/* comment (optional) */
/* price */

CONSTRAINT pk_invested_asset PRIMARY KEY (pk_invested_asset),
CONSTRAINT fk_investor FOREIGN KEY (fk_investor) REFERENCES INVESTORS,
CONSTRAINT fk_subject FOREIGN KEY (fk_subject) REFERENCES SUBJECTS,
CONSTRAINT fk_currency FOREIGN KEY (fk_currency) REFERENCES CURRENCIES
);

CREATE TABLE BONUSES (
pk_bonus INT,
fk_investor INT,
fk_subject INT,

/* date */
/* short_name */
/* description */
/* comment (optional) */
/* reward */

CONSTRAINT pk_bonuses PRIMARY KEY (pk_bonuses),
CONSTRAINT fk_investor FOREIGN KEY (fk_investor) REFERENCES INVESTORS,
CONSTRAINT fk_subject FOREIGN KEY (fk_subject) REFERENCES SUBJECTS
);

CREATE TABLE INVESTED_MONEY (
pk_invested_money INT,
fk_investor INT,
fk_subject INT,
fk_currency INT,

/* date */
/* short_name */
/* description */
/* comment (optional) */
/* amount */

CONSTRAINT pk_invested_money PRIMARY KEY (pk_invested_money),
CONSTRAINT fk_investor FOREIGN KEY (fk_investor) REFERENCES INVESTORS,
CONSTRAINT fk_subject FOREIGN KEY (fk_subject) REFERENCES SUBJECTS,
CONSTRAINT fk_currency FOREIGN KEY (fk_currency) REFERENCES CURRENCIES
);

