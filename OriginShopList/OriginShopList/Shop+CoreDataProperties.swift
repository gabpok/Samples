//
//  Shop+CoreDataProperties.swift
//  OriginShopList
//
//  Created by Gabriela Pokropska on 29/09/2020.
//  Copyright © 2020 Gabriela Pokropska. All rights reserved.
//
//

import Foundation
import CoreData


extension Shop {

    @nonobjc public class func fetchRequest() -> NSFetchRequest<Shop> {
        return NSFetchRequest<Shop>(entityName: "Shop")
    }

    @NSManaged public var id_list: UUID?
    @NSManaged public var listName: String?
    @NSManaged public var itemName: String?
    @NSManaged public var localization: String?
    @NSManaged public var item: NSSet?
    
    public var wrappedListName: String {
        listName ?? "Unknown list"
    }
    
    public var wrappedItemName: String {
        itemName ?? "Unknown item"
    }
    
    public var wrappedLocalization: String {
        localization ?? "Unknown localization"
    }
    
    public var itemArray: [Item] {
        let set = item as? Set<Item> ?? []
        return set.sorted {
            $0.wrappedName < $1.wrappedName
        }
    }
}

// MARK: Generated accessors for item
extension Shop {

    @objc(addItemObject:)
    @NSManaged public func addToItem(_ value: Item)

    @objc(removeItemObject:)
    @NSManaged public func removeFromItem(_ value: Item)

    @objc(addItem:)
    @NSManaged public func addToItem(_ values: NSSet)

    @objc(removeItem:)
    @NSManaged public func removeFromItem(_ values: NSSet)

}
