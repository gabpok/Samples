//
//  AddListView.swift
//  OriginShopList
//
//  Created by Gabriela Pokropska on 29/09/2020.
//  Copyright © 2020 Gabriela Pokropska. All rights reserved.
//

import SwiftUI

struct AddListView: View {
    @Environment(\.managedObjectContext) var moc
    @Environment(\.presentationMode) var presentation
    
    @State private var listName: String = ""
    @State private var localization: String = ""
    
    var body: some View {
        UINavigationBar.appearance().largeTitleTextAttributes = [.foregroundColor: UIColor(named: "title")!]
        UINavigationBar.appearance().titleTextAttributes = [.foregroundColor: UIColor(named: "title")!]
        
        return NavigationView {
            VStack(alignment: .center, spacing: 15) {
                TextField("List name", text: $listName)
                    .padding()
                    .background(Color("background_textfield"))
                    .frame(width: 400, height: 50)
                TextField("Shop's localization", text: $localization)
                    .padding()
                    .background(Color("background_textfield"))
                    .frame(width: 400, height: 50)
                
                Button("Save") {
                    let shopList = Shop(context: self.moc)
                    shopList.listName = self.listName
                    shopList.localization = self.localization
                    
                    try? self.moc.save()
                    self.presentation.wrappedValue.dismiss()
                }.font(.headline)
                .foregroundColor(Color("text"))
                .padding()
                .frame(width: 150, height: 50)
                .background(Color("background_button"))
                .cornerRadius(15.0)
                
                Button("Cancel") {
                    self.presentation.wrappedValue.dismiss()
                }.font(.headline)
                .foregroundColor(Color("text"))
                .padding()
                .frame(width: 150, height: 50)
                .background(Color("background_button"))
                .cornerRadius(15.0)
            }
        }.navigationBarTitle("Add list")
    }
}

struct AddListView_Previews: PreviewProvider {
    static var previews: some View {
        AddListView()
    }
}
