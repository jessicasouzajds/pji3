-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema pji3
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema pji3
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `pji3` DEFAULT CHARACTER SET utf8 ;
USE `pji3` ;

-- -----------------------------------------------------
-- Table `pji3`.`Nodo`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `pji3`.`Nodo` (
  `idNodo` VARCHAR(12) NOT NULL,
  PRIMARY KEY (`idNodo`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `pji3`.`Gateway`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `pji3`.`Gateway` (
  `idGateway` VARCHAR(12) NOT NULL,
  PRIMARY KEY (`idGateway`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `pji3`.`Sensor`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `pji3`.`Sensor` (
  `idSensor` INT NOT NULL AUTO_INCREMENT,
  `Tipo` VARCHAR(45) NOT NULL,
  `idNodo` VARCHAR(12) NOT NULL,
  PRIMARY KEY (`idSensor`, `idNodo`),
  INDEX `fk_Sensor_Nodo_idx` (`idNodo` ASC),
  CONSTRAINT `fk_Sensor_Nodo`
    FOREIGN KEY (`idNodo`)
    REFERENCES `pji3`.`Nodo` (`idNodo`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `pji3`.`Dado`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `pji3`.`Dado` (
  `idDado` INT NOT NULL AUTO_INCREMENT,
  `idSensor` INT NOT NULL,
  `idGateway` VARCHAR(12) NOT NULL,
  `Dado` VARCHAR(45) NOT NULL,
  `RSSI` INT NOT NULL,
  PRIMARY KEY (`idDado`),
  INDEX `fk_Nodo_has_Gateway_Gateway1_idx` (`idGateway` ASC),
  INDEX `fk_Dado_Sensor1_idx` (`idSensor` ASC),
  CONSTRAINT `fk_Gateway`
    FOREIGN KEY (`idGateway`)
    REFERENCES `pji3`.`Gateway` (`idGateway`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Sensor`
    FOREIGN KEY (`idSensor`)
    REFERENCES `pji3`.`Sensor` (`idSensor`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

