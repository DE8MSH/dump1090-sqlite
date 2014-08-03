CREATE TABLE flightslog ( 
    df          SMALLINT( 2 ),
    modes       CHAR( 6 )          UNIQUE ON CONFLICT REPLACE,
    country     CHAR( 2 ),
    flight      VARCHAR( 7 ),
    airline     CHAR( 3 ),
    squawk      INT( 4 ),
    regn        VARCHAR( 16 ),
    type        VARCHAR( 16 ),
    alt         INT( 6 ),
    vr          SMALLINT( 2 ),
    lat         DECIMAL( 17, 14 ),
    lon         DECIMAL( 17, 14 ),
    heading     INT( 6 ),
    speed       INT( 6 ),
    msgs        INT( 6 ),
    last_update TIMESTAMP          DEFAULT ( CURRENT_TIMESTAMP ) 
);

CREATE TABLE trackslog ( 
    id          INTEGER            PRIMARY KEY AUTOINCREMENT,
    modes       CHAR( 6 ),
    alt         INT( 6 ),
    lat         DECIMAL( 17, 14 ),
    lon         DECIMAL( 17, 14 ),
    last_update TIMESTAMP          DEFAULT ( CURRENT_TIMESTAMP ) 
);

CREATE VIEW planes AS
       SELECT f.modes,
              a.modescountry,
              a.registration,
              a.type,
              f.last_update
         FROM flightslogs f
              JOIN Aircraft a
                ON ( f.modes = a.modes );


